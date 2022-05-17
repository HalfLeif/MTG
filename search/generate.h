#include <algorithm>
#include <cmath>
#include <memory>
#include <mutex>
#include <numeric>
#include <set>
#include <thread>
#include <unordered_map>
#include <vector>

#include "../common/container.h"
#include "../common/debug.h"
#include "../common/random.h"
#include "../core/contribution.h"
#include "../core/library.h"
#include "../core/spell.h"
#include "search.h"

// Params at top in order to quickly reduce for debugging purposes.

// Number of threads determines how many gradient descents will run in parallel.
constexpr int kThreads = 16;
constexpr int kDescentDepth = 125;
constexpr int kPrintTopN = 3;
constexpr double kChangeSizeRate = 0.01;
constexpr int kSeed = 3;

// Sampling temperature. Higher temperature -> more flat distribution.
// Lower temperature (close to 0) -> more focused distribution.
constexpr double kSampleTemp = 0.07;

// Keep top X% of items for sampling.
// E.g. 23 cards -> keep 9.
constexpr double kTopPart = 0.40;

// LandSearch determines how many iterations are spent to optimize the land
// distribution for a particular deck. Games on the other hand is used to
// specify for how many games a deck should be evaluated, using the optimal land
// distribution.
constexpr int kFastLandSearch = 120;
constexpr int kFastGames = 400;

constexpr int kDeepLandSearch = 500;
constexpr int kDeepGames = 1000;

// For debugging purposes:
// constexpr int kFastLandSearch = 10;
// constexpr int kFastGames = 5;
//
// constexpr int kDeepLandSearch = 7;
// constexpr int kDeepGames = 50;

constexpr int kMaxColors = 3;

// Uniformly samples `wanted` cards from [0,total). Any `forced_cards` are
// automatically picked.
std::vector<int> GeneratePermutation(const std::vector<int> &available_ids,
                                     const int wanted,
                                     const std::set<int> &forced_cards,
                                     ThreadsafeRandom &rand) {
  for (int f : forced_cards) {
    if (!ContainsItem(available_ids, f)) {
      FATAL << "Forced card " << f << " not available!" << std::endl;
    }
  }

  std::vector<int> permutation;
  if (forced_cards.size() > wanted) {
    ERROR << "Already have more cards than wanted." << std::endl;
    return permutation;
  }

  std::vector<int> shuffled;
  shuffled.reserve(available_ids.size());
  permutation.reserve(wanted);
  for (int id : available_ids) {
    if (ContainsKey(forced_cards, id)) {
      // Already picked.
      permutation.push_back(id);
    } else {
      // Available for sampling.
      shuffled.push_back(id);
    }
  }

  rand.Shuffle(shuffled);
  for (int i = 0; i < shuffled.size() && permutation.size() < wanted; ++i) {
    permutation.push_back(shuffled[i]);
  }

  return permutation;
}

std::unique_ptr<Library>
ApplyPermutation(const std::vector<Spell> &available_cards,
                 const std::vector<int> &permutation) {
  Library::Builder builder;
  builder.SetLimited();
  for (int index : permutation) {
    builder.AddSpell(available_cards[index]);
  }
  return builder.BuildUnique();
}

// How many cards should be replaced depending on iteration number. Later
// iterations replace fewer cards.
// Corresponds to decaying learning rate.
int NumReplace(const int iteration_nr) {
  if (iteration_nr < 0.10 * kDescentDepth) {
    return 10;
  }
  if (iteration_nr < 0.35 * kDescentDepth) {
    return 7;
  }
  if (iteration_nr < 0.60 * kDescentDepth) {
    return 5;
  }
  if (iteration_nr < 0.80 * kDescentDepth) {
    return 3;
  }
  if (iteration_nr < 0.90 * kDescentDepth) {
    return 2;
  }
  return 1;
}

// Deterministic implementation.
std::vector<int>
OldSelectCardsToReplace(const std::unordered_map<int, const Contribution *>
                            &permutation_to_contributions,
                        const std::set<int> &forced_cards, int min_replace) {
  std::vector<std::pair<double, int>> scores;
  for (const auto &[index, contribution] : permutation_to_contributions) {
    // Note: `score/sqrt(1+mana)` still biases heavier cards, but is less biased
    // than simply score. However, `score/sqrt(mana)` favors single mana cards
    // way too highly.
    const double usefulness = contribution->GetContribution() /
                              std::sqrt(1 + contribution->mana_value());
    scores.emplace_back(usefulness, index);
  }
  std::sort(scores.begin(), scores.end());

  std::vector<int> to_replace;
  to_replace.reserve(min_replace);

  for (const auto &[score, index] : scores) {
    if (ContainsKey(forced_cards, index)) {
      // Forced cards cannot be considered for replacement.
      continue;
    }
    if (score <= 0) {
      // Replace useless card
      to_replace.push_back(index);
    } else if (to_replace.size() < min_replace) {
      // Replace up to N bad cards
      to_replace.push_back(index);
    } else {
      // Already found enough bad cards.
      break;
    }
  }
  return to_replace;
}

// Selects cards to replace based on their contributions.
//
// Currently is biased towards replacing cards of lower mana value, which can
// cause the algorithm to get stuck in local minima.
//
// Ideas to avoid local minima, at possible cost of convergence:
// - (done) decaying learning rate,
// - (bad) random mutations,
// - (done) modify distribution to avoid penalize low mana cards,
// - (done) sample instead of merely pick lowest score (Stochastic Gradient).
// - (done) temperature sampling.
// - (done) top K sampling.
std::vector<int>
SelectCardsToReplace(const std::unordered_map<int, const Contribution *>
                         &permutation_to_contributions,
                     const std::set<int> &forced_cards, const int min_replace,
                     ThreadsafeRandom &random) {
  std::vector<int> to_replace;
  to_replace.reserve(min_replace);

  // Build a random distribution of what cards to keep.
  std::vector<std::pair<double, int>> distribution;
  for (const auto &[index, contribution] : permutation_to_contributions) {
    if (ContainsKey(forced_cards, index)) {
      // Forced cards cannot be considered for replacement.
      continue;
    }
    const double contribution_score = contribution->GetContribution();
    if (contribution_score <= 0) {
      to_replace.push_back(index);
      continue;
    }
    // Note: `score/sqrt(1+mana)` still biases heavier cards, but is less biased
    // than simply score. However, `score/sqrt(mana)` favors single mana cards
    // way too highly.
    const double usefulness =
        contribution_score / std::sqrt(1 + contribution->mana_value());
    double prob = 1 / usefulness;
    prob = std::exp(std::log(prob) / kSampleTemp);
    distribution.emplace_back(prob, index);
  }

  // Restrict sampling to top K least useful cards.
  std::sort(distribution.begin(), distribution.end(),
            std::greater<std::pair<double, int>>());
  int topk = static_cast<int>(kTopPart * distribution.size());
  if (topk < min_replace) {
    topk = min_replace;
  }
  if (topk < distribution.size()) {
    distribution.resize(topk);
  }

  if (to_replace.size() >= min_replace) {
    return to_replace;
  }
  const int left_replace = min_replace - to_replace.size();

  // Sum up total for normalization.
  double distribution_total = 0;
  for (const auto [prob, index] : distribution) {
    distribution_total += prob;
  }

  // Sample cards to replace.
  while (to_replace.size() < left_replace && !distribution.empty()) {
    int pos = SampleOne(distribution, random.RandOne(), distribution_total);
    distribution_total -= distribution[pos].first;
    distribution[pos].first = 0;
    to_replace.push_back(distribution[pos].second);
  }
  return to_replace;
}

// Given a range of [0..total-1], return all numbers not present in subset.
std::vector<int> InvertSubset(const std::vector<int> &subset,
                              const std::vector<int> &all_cards) {
  std::vector<int> inverted;
  inverted.reserve(all_cards.size());
  for (int id : all_cards) {
    if (!ContainsItem(subset, id)) {
      inverted.push_back(id);
    }
  }
  return inverted;
}

// Returns a new "permutation" given a permutation, and what elements of
// permutation should be replaced.
// `to_replace` must be a subset of `permutation`.
// `total` signifies the total number of available cards.
std::vector<int> ReplaceBadCards(const std::vector<int> &permutation,
                                 const std::vector<int> &to_replace,
                                 const std::vector<int> &all_cards,
                                 ThreadsafeRandom &rand) {
  CHECK(!to_replace.empty());
  // Stores one position of a replaced card.
  int replaced_position = -1;

  std::vector<int> pool = InvertSubset(permutation, all_cards);

  std::vector<int> new_permutation;
  new_permutation.reserve(permutation.size());
  for (const int index : permutation) {
    if (!pool.empty() && ContainsItem(to_replace, index)) {
      // Choose a different card randonly.
      replaced_position = new_permutation.size();
      int choice = rand.Rand() % pool.size();
      MoveItem(choice, pool, new_permutation);
    } else {
      new_permutation.push_back(index);
    }
  }

  // Chance to modify deck size
  if (const double r = rand.RandOne(); r < kChangeSizeRate) {
    // Increase deck size if there are still available cards.
    if (!pool.empty()) {
      int choice = rand.Rand() % pool.size();
      MoveItem(choice, pool, new_permutation);
    }
  } else if (r < 2 * kChangeSizeRate) {
    // Decrease deck size. Prefer to remove a newly added card.
    if (replaced_position < 0) {
      // Can happen when pools are very small. If so, replace any card, even
      // a forced card. Should happen very rarely.
      replaced_position = 0;
    }
    new_permutation[replaced_position] = new_permutation.back();
    new_permutation.pop_back();
  }
  return new_permutation;
}

bool ColorsIn(const Spell &spell, const ManaCost &mana) {
  for (const auto [color, amount] : spell.cost) {
    if (!mana.contains(color)) {
      return false;
    }
  }
  return true;
}

TEST(ColorsIn) {
  EXPECT_TRUE(ColorsIn(MakeSpell("W3"), ParseMana("W")));
  EXPECT_TRUE(ColorsIn(MakeSpell("W3"), ParseMana("WB")));
  EXPECT_TRUE(ColorsIn(MakeSpell("WB3"), ParseMana("WB")));
  EXPECT_TRUE(ColorsIn(MakeSpell("WB3"), ParseMana("WBUG")));
}

std::vector<int> FilterOnMana(const std::vector<Spell> &available_cards,
                              const std::set<int> &forced_cards,
                              const ManaCost &mana) {
  std::vector<int> result;
  for (int i = 0; i < available_cards.size(); ++i) {
    if (ColorsIn(available_cards[i], mana) || ContainsKey(forced_cards, i)) {
      result.push_back(i);
    }
  }
  return result;
}

struct GeneratedDeck {
  std::vector<int> permutation;

  // Note: must keep lib here, since param has pointer to lib.
  std::unique_ptr<Library> lib;
  Param param;
  double score;
  CardContributions contributions;
  int iteration_nr = 0;
};

// Only return the best one. That way gets more diversity between best N decks.
std::unique_ptr<GeneratedDeck>
GradientDescent(const std::vector<Spell> &available_cards,
                const ManaCost &colors, const std::set<int> &forced_cards,
                int seed) {
  ThreadsafeRandom rand(seed);
  // Keep track of best permutations.
  std::vector<std::unique_ptr<GeneratedDeck>> iterations;

  // 0. Filter available cards to chosen colors.
  const std::vector<int> available_ids =
      FilterOnMana(available_cards, forced_cards, colors);

  // 1. Create a random starting deck.
  // Limited: 23 spells, 17 lands.
  std::vector<int> permutation =
      GeneratePermutation(available_ids, 23, forced_cards, rand);

  for (int i = 0; i < kDescentDepth; ++i) {
    if (PARANOIA) {
      for (int p : forced_cards) {
        if (!ContainsItem(permutation, p)) {
          FATAL << "Permutation does not include forced card " << p
                << " at descent " << i << std::endl;
        }
      }
    }

    auto generated = std::make_unique<GeneratedDeck>();
    generated->iteration_nr = i;

    // 2. Find best land distribution for small number of iterations.
    generated->lib = ApplyPermutation(available_cards, permutation);
    generated->param =
        CompareParams(*generated->lib, rand, kFastLandSearch, false);

    // 3. Track contributions per card.
    std::unordered_map<int, const Contribution *> permutation_to_contributions;
    generated->contributions = MakeContributionMaps(
        available_cards, permutation, &permutation_to_contributions);
    generated->score = RunParam(*generated->lib, generated->param, kFastGames,
                                rand, &generated->contributions);

    // 4. Replace bad cards for next iteration.
    generated->permutation = std::move(permutation);
    // const std::vector<int> to_replace = OldSelectCardsToReplace(
    //     permutation_to_contributions, forced_cards, NumReplace(i));
    const std::vector<int> to_replace = SelectCardsToReplace(
        permutation_to_contributions, forced_cards, NumReplace(i), rand);
    permutation = ReplaceBadCards(generated->permutation, to_replace,
                                  available_ids, rand);
    iterations.push_back(std::move(generated));
  }

  std::sort(iterations.begin(), iterations.end(),
            [](const auto &a, const auto &b) { return a->score > b->score; });
  return std::move(iterations[0]);
}

std::vector<std::unique_ptr<GeneratedDeck>>
EvaluateBestDecks(const std::vector<std::unique_ptr<GeneratedDeck>> &decks,
                  const std::vector<Spell> &available_cards) {
  std::vector<std::thread> threads;
  threads.reserve(decks.size());
  std::vector<std::unique_ptr<GeneratedDeck>> re_evaluated;
  re_evaluated.reserve(decks.size());
  std::mutex mutex;
  for (int i = 0; i < decks.size(); ++i) {
    // Must take `i` by value, not reference.
    threads.emplace_back([&, i]() {
      ThreadsafeRandom rand(i);
      auto generated = std::make_unique<GeneratedDeck>();
      generated->iteration_nr = decks[i]->iteration_nr;
      generated->permutation = decks[i]->permutation;
      generated->contributions = MakeContributionMaps(
          available_cards, generated->permutation, nullptr);
      generated->lib =
          ApplyPermutation(available_cards, generated->permutation);
      generated->param = CompareParams(*generated->lib, rand, kDeepLandSearch,
                                       /*print=*/false);
      generated->score = RunParam(*generated->lib, generated->param, kDeepGames,
                                  rand, &generated->contributions);

      MutexLock lock(&mutex);
      re_evaluated.push_back(std::move(generated));
    });
  }
  for (std::thread &thread : threads) {
    thread.join();
  }
  std::sort(re_evaluated.begin(), re_evaluated.end(),
            [](const auto &a, const auto &b) { return a->score > b->score; });
  return re_evaluated;
}

std::vector<std::unique_ptr<GeneratedDeck>>
RunMultipleDescent(const std::vector<Spell> &available_cards,
                   const std::set<int> &forced_cards,
                   const std::vector<ManaCost> &combinations) {
  std::vector<std::unique_ptr<GeneratedDeck>> all_decks;
  std::vector<std::thread> threads;
  std::mutex mutex;
  for (int i = 0; i < kThreads; ++i) {
    // Must take `i` by value, not reference. Otherwise several threads will
    // have the same value and redo the same computation.
    threads.emplace_back([&, i]() {
      const ManaCost &colors = combinations[i % combinations.size()];
      std::unique_ptr<GeneratedDeck> more =
          GradientDescent(available_cards, colors, forced_cards, kSeed + i);

      MutexLock lock(&mutex);
      all_decks.push_back(std::move(more));
    });
  }
  for (std::thread &thread : threads) {
    thread.join();
  }
  std::sort(all_decks.begin(), all_decks.end(),
            [](const auto &a, const auto &b) { return a->score > b->score; });
  return all_decks;
}

// Returns vector of spells where each spell corresponds to an element
// available_cards. Supports duplicate cards. Takes spell info from all_cards.
std::vector<Spell>
FilterCards(const std::vector<Spell> &all_cards,
            const std::vector<std::string_view> &available_cards) {
  std::unordered_map<std::string_view, const Spell *> spells_by_name;
  spells_by_name.reserve(all_cards.size());
  for (const Spell &spell : all_cards) {
    spells_by_name[spell.name] = &spell;
  }
  std::vector<Spell> result;
  result.reserve(available_cards.size());
  std::vector<std::string_view> missing_spells;
  for (const std::string_view cardname : available_cards) {
    const Spell *spell = FindPtrOrNull(spells_by_name, cardname);
    if (spell == nullptr) {
      missing_spells.push_back(cardname);
      continue;
    }
    if (spell->cost.Total() == 0) {
      // Happens for Lands and transformed cards.
      continue;
    }
    result.push_back(*spell);
  }
  for (std::string_view cardname : missing_spells) {
    ERROR << "Spell " << cardname << " is not listed in all_cards" << std::endl;
  }
  CHECK(missing_spells.empty());
  return result;
}

TEST(FilterCardsSupportsDuplicateCards) {
  std::vector<Spell> spells;
  spells.push_back(MakeSpell("B2", 1, "Foo"));
  std::vector<Spell> filtered = FilterCards(spells, {"Foo", "Foo"});
  EXPECT_EQ(filtered.size(), 2);
  for (SpellView spell : filtered) {
    EXPECT_EQ(spell.name(), "Foo");
  }
}

// Finds the indices of the `forced_card_names` in `available_cards`. In case of
// duplicates, only so many instances are included as in `forced_card_names`.
std::set<int>
FindForcedCards(const std::vector<Spell> &available_cards,
                const std::vector<std::string_view> &forced_card_names) {
  std::unordered_map<std::string_view, std::vector<int>> name_to_index;
  name_to_index.reserve(available_cards.size());
  for (int i = 0; i < available_cards.size(); ++i) {
    const Spell &spell = available_cards[i];
    name_to_index[spell.name].push_back(i);
  }

  std::set<int> forced_indices;
  for (const std::string_view name : forced_card_names) {
    std::vector<int> *instances = FindOrNull(name_to_index, name);
    if (instances == nullptr) {
      FATAL << "Forced card not found among available_cards: " << name
            << std::endl;
    }
    CHECK(!instances->empty())
        << "Forced card is already picked: " << name << std::endl;
    forced_indices.insert(instances->back());
    instances->pop_back();
  }

  return forced_indices;
}

void PrintGeneratedDecksShort(
    const std::vector<std::unique_ptr<GeneratedDeck>> &decks) {
  for (int i = 0; i < decks.size() && i < 10; ++i) {
    std::cout << decks[i]->score << " iteration " << decks[i]->iteration_nr
              << std::endl;
  }
}

void PrintGeneratedDecksDetailed(
    const std::vector<Spell> &available_cards,
    const std::vector<std::unique_ptr<GeneratedDeck>> &best) {
  std::cout << "\nFound the best generated decks! " << std::endl;
  for (int i = 0; i < best.size(); ++i) {
    const GeneratedDeck &generated = *best[i];
    std::cout << std::endl;
    std::cout << "Score: " << generated.score << std::endl;
    std::cout << "Iteration: " << generated.iteration_nr << std::endl;
    // std::cout << best[i]->param << std::endl;

    Deck deck = TournamentDeck(generated.param);
    // std::cout << deck << std::endl;
    PrintLands(deck);
    if (i < kPrintTopN) {
      // Only print detailed decks for best N.
      PrintContributions(deck, generated.contributions);
    }
  }
}

void GenerateDeck(const std::vector<Spell> &available_cards,
                  const std::set<int> &forced_cards,
                  const std::vector<ManaCost> &combinations) {
  std::vector<std::unique_ptr<GeneratedDeck>> all_decks =
      RunMultipleDescent(available_cards, forced_cards, combinations);

  // TODO: Unique the decks, currently generates duplicates.
  PrintGeneratedDecksShort(all_decks);

  // Re-evaluate 8 best decks, to find the best one.
  std::vector<std::unique_ptr<GeneratedDeck>> best_decks =
      EvaluateBestDecks(all_decks, available_cards);
  PrintGeneratedDecksDetailed(available_cards, best_decks);
}

// -----------------------------------------------------------------------------

TEST(FilterOnMana) {
  std::vector<Spell> available_cards;
  available_cards.push_back(MakeSpell("B", 1, ""));      // 0
  available_cards.push_back(MakeSpell("R", 1, ""));      // 1
  available_cards.push_back(MakeSpell("W", 1, "Angel")); // 2
  available_cards.push_back(MakeSpell("BR", 1, ""));
  available_cards.push_back(MakeSpell("G", 1, ""));
  available_cards.push_back(MakeSpell("GW", 1, ""));
  available_cards.push_back(MakeSpell("W", 1, "Citizen"));

  auto available = FilterOnMana(available_cards, {2}, ParseMana("BR"));
  EXPECT_EQ(available.size(), 4);
  EXPECT_TRUE(ContainsItem(available, 0));
  EXPECT_TRUE(ContainsItem(available, 1));
  EXPECT_TRUE(ContainsItem(available, 2));
  EXPECT_TRUE(ContainsItem(available, 3));

  // Not BR, and not forced.
  EXPECT_FALSE(ContainsItem(available, 4));
  EXPECT_FALSE(ContainsItem(available, 5));
  EXPECT_FALSE(ContainsItem(available, 6));
}

bool AreInRange(const std::vector<int> &permutation, const int max) {
  for (const int p : permutation) {
    if (0 <= p && p < max) {
      continue;
    } else {
      return false;
    }
  }
  return true;
}

bool IsSubset(const std::set<int> &forced, const std::set<int> &picked) {
  for (int p : forced) {
    if (!ContainsKey(picked, p)) {
      return false;
    }
  }
  return true;
}

std::vector<int> Consecutive(int total) {
  std::vector<int> result;
  result.reserve(total);
  for (int i = 0; i < total; ++i) {
    result.push_back(i);
  }
  return result;
}

TEST(InvertSubset) {
  std::vector<int> inverted = InvertSubset({2, 3, 4, 8}, Consecutive(10));
  EXPECT_EQ(inverted.size(), 6);
  EXPECT_TRUE(ContainsItem(inverted, 0));
  EXPECT_TRUE(ContainsItem(inverted, 1));
  EXPECT_TRUE(ContainsItem(inverted, 5));
  EXPECT_FALSE(ContainsItem(inverted, 2));
  EXPECT_FALSE(ContainsItem(inverted, 8));
}

TEST(GeneratePermutationWithinLimits) {
  ThreadsafeRandom rand;
  std::set<int> forced_cards = {24, 27, 31};
  std::vector<int> permutation =
      GeneratePermutation(Consecutive(32), 23, forced_cards, rand);
  EXPECT_EQ(permutation.size(), 23);
  EXPECT_TRUE(AreInRange(permutation, 100));

  std::set<int> picked(permutation.begin(), permutation.end());
  // No duplicate
  EXPECT_EQ(picked.size(), permutation.size());
  EXPECT_TRUE(IsSubset(forced_cards, picked));
}

TEST(GeneratePermutationWhenForcedCardsAlreadyMaximum) {
  ThreadsafeRandom rand;
  std::set<int> forced_cards = {0, 1, 2};
  std::vector<int> permutation =
      GeneratePermutation(Consecutive(32), 3, forced_cards, rand);
  EXPECT_EQ(permutation.size(), 3);

  std::set<int> picked(permutation.begin(), permutation.end());
  EXPECT_TRUE(IsSubset(forced_cards, picked));
}

TEST(SelectCardsToReplaceRemovesLowestContributionPerManaValue) {
  ThreadsafeRandom random(123);
  std::vector<Spell> available_cards;
  available_cards.push_back(MakeSpell("B1", 1, "Bloodseeker"));
  available_cards.push_back(MakeSpell("B2", 1, "Stinger"));
  available_cards.push_back(MakeSpell("WW3", 1, "Invitation"));
  available_cards.push_back(MakeSpell("BB9", 1, "Bad"));

  std::vector<int> permutation = {3, 1, 2, 0};
  std::unordered_map<int, const Contribution *> permutation_to_contributions;
  CardContributions contributions = MakeContributionMaps(
      available_cards, permutation, &permutation_to_contributions);

  AddDelta(1, "Bloodseeker", &contributions);
  AddDelta(3.5, "Stinger", &contributions);
  AddDelta(1.1, "Bad", &contributions);
  AddDelta(6, "Invitation", &contributions);

  std::vector<int> to_replace =
      SelectCardsToReplace(permutation_to_contributions, {}, 1, random);
  CHECK(to_replace.size() == 1);
  // Removes lowest contribution per mana.
  EXPECT_EQ(available_cards[to_replace[0]].name, "Bad");
}

TEST(SelectCardsToReplaceRespectForcedCards) {
  ThreadsafeRandom random;
  std::vector<Spell> available_cards;
  available_cards.push_back(MakeSpell("W", 1, "Minister"));
  available_cards.push_back(MakeSpell("WW3", 1, "Invitation"));
  available_cards.push_back(MakeSpell("BB3", 1, "Security"));

  std::vector<int> permutation = {0, 1, 2};
  std::unordered_map<int, const Contribution *> permutation_to_contributions;
  CardContributions contributions = MakeContributionMaps(
      available_cards, permutation, &permutation_to_contributions);

  AddDelta(0.001, "Minister", &contributions);
  AddDelta(4, "Security", &contributions);
  AddDelta(600, "Invitation", &contributions);

  std::vector<int> to_replace =
      SelectCardsToReplace(permutation_to_contributions, {0}, 1, random);
  CHECK(to_replace.size() == 1);
  // Remove lowest contribution, except Minister which is forced.
  EXPECT_EQ(available_cards[to_replace[0]].name, "Security");
}

TEST(ReplaceBadCards) {
  ThreadsafeRandom rand;
  std::vector<int> permutation = {3, 1, 2, 0};
  std::vector<int> to_replace = {1, 2};

  std::vector<int> new_permutation =
      ReplaceBadCards(permutation, to_replace, Consecutive(10), rand);
  CHECK(permutation.size() == new_permutation.size());
  // Unchanged
  EXPECT_EQ(new_permutation[0], 3);
  EXPECT_EQ(new_permutation[3], 0);

  // New cards must be greater than 3
  EXPECT_LT(3, new_permutation[1]);
  EXPECT_LT(3, new_permutation[2]);
}

TEST(FindForcedCards) {
  std::vector<Spell> available_cards;
  available_cards.push_back(MakeSpell("B2", 1, "Other"));
  available_cards.push_back(MakeSpell("B2", 1, "Other"));
  available_cards.push_back(MakeSpell("B2", 1, "Foo caster"));
  available_cards.push_back(MakeSpell("B2", 1, "Other"));

  std::vector<std::string_view> forced_card_names = {"Foo caster"};

  std::set<int> indices = FindForcedCards(available_cards, forced_card_names);
  EXPECT_EQ(indices.size(), forced_card_names.size());

  EXPECT_EQ(available_cards[*indices.begin()].name, "Foo caster");
}

TEST(FindForcedCardsAddsDuplicatesAsSeparateInstances) {
  std::vector<Spell> available_cards;
  available_cards.push_back(MakeSpell("B2", 1, "Other"));
  available_cards.push_back(MakeSpell("B2", 1, "Other"));
  available_cards.push_back(MakeSpell("B2", 1, "Foo caster"));
  available_cards.push_back(MakeSpell("B2", 1, "Other"));
  available_cards.push_back(MakeSpell("B2", 1, "Foo caster"));
  available_cards.push_back(MakeSpell("B2", 1, "Foo caster"));
  available_cards.push_back(MakeSpell("B2", 1, "Other"));

  std::vector<std::string_view> forced_card_names = {"Foo caster",
                                                     "Foo caster"};

  std::set<int> indices = FindForcedCards(available_cards, forced_card_names);
  EXPECT_EQ(indices.size(), forced_card_names.size());

  for (int p : indices) {
    EXPECT_EQ(available_cards[p].name, "Foo caster");
  }
}
