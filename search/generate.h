#include <algorithm>
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
constexpr double kChangeSizeRate = 0.05;

// LandSearch determines how many iterations are spent to optimize the land
// distribution for a particular deck. Games on the other hand is used to
// specify for how many games a deck should be evaluated, using the optimal land
// distribution.
constexpr int kFastLandSearch = 100;
constexpr int kFastGames = 350;

constexpr int kDeepLandSearch = 500;
constexpr int kDeepGames = 1000;

// For debugging purposes:
// constexpr int kFastLandSearch = 10;
// constexpr int kFastGames = 5;
//
// constexpr int kDeepLandSearch = 7;
// constexpr int kDeepGames = 50;

// Uniformly samples `wanted` cards from [0,total). Any `forced_cards` are
// automatically picked.
std::vector<int> GeneratePermutation(const int total, const int wanted,
                                     const std::set<int> &forced_cards,
                                     ThreadsafeRandom &rand) {
  std::vector<int> permutation;
  if (wanted > total) {
    ERROR << "Cannot request more cards than there are." << std::endl;
    return permutation;
  }
  if (forced_cards.size() > wanted) {
    ERROR << "Already have more cards than wanted." << std::endl;
    return permutation;
  }

  std::vector<int> shuffled;
  shuffled.reserve(total);
  permutation.reserve(wanted);
  for (int i = 0; i < total; ++i) {
    if (ContainsKey(forced_cards, i)) {
      // Already picked.
      permutation.push_back(i);
    } else {
      // Available for sampling.
      shuffled.push_back(i);
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

std::vector<int>
SelectCardsToReplace(const std::unordered_map<int, const Contribution *>
                         &permutation_to_contributions,
                     const std::set<int> &forced_cards, int min_replace) {
  std::vector<std::pair<double, int>> scores;
  for (const auto &[index, contribution] : permutation_to_contributions) {
    const double usefulness = contribution->GetContribution();
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

std::vector<int> ReplaceBadCards(const std::vector<int> &permutation,
                                 const std::vector<int> &to_replace,
                                 const int total, ThreadsafeRandom &rand) {
  // Stores one position of a replaced card.
  int replaced_position = -1;

  std::vector<int> new_permutation;
  new_permutation.reserve(permutation.size());
  for (const int index : permutation) {
    int new_index = index;
    if (ContainsItem(to_replace, index)) {
      // Choose a different card randonly.
      while (ContainsItem(permutation, new_index) ||
             ContainsItem(new_permutation, new_index)) {
        new_index = rand.Rand() % total;
      }
      replaced_position = new_permutation.size();
    }
    new_permutation.push_back(new_index);
  }

  // Chance to modify deck size
  if (const double r = rand.RandOne(); r < kChangeSizeRate) {
    // Increase deck size
    int new_index = rand.Rand() % total;
    while (ContainsItem(permutation, new_index) ||
           ContainsItem(new_permutation, new_index)) {
      new_index = rand.Rand() % total;
    }
    new_permutation.push_back(new_index);
  } else if (r < 2 * kChangeSizeRate) {
    // Decrease deck size. Must only remove a "bad" card.
    CHECK(replaced_position > 0);
    new_permutation[replaced_position] = new_permutation.back();
    new_permutation.pop_back();
  }
  return new_permutation;
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
                const std::set<int> &forced_cards, int seed) {
  ThreadsafeRandom rand(seed);
  // Keep track of best permutations.
  std::vector<std::unique_ptr<GeneratedDeck>> iterations;

  // 1. Create a random starting deck.
  // Limited: 23 spells, 17 lands.
  std::vector<int> permutation =
      GeneratePermutation(available_cards.size(), 23, forced_cards, rand);

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
    const std::vector<int> to_replace = SelectCardsToReplace(
        permutation_to_contributions, forced_cards, NumReplace(i));
    permutation = ReplaceBadCards(generated->permutation, to_replace,
                                  available_cards.size(), rand);
    iterations.push_back(std::move(generated));
  }

  std::sort(iterations.begin(), iterations.end(),
            [](const auto &a, const auto &b) { return a->score > b->score; });
  return std::move(iterations[0]);
}

std::vector<std::unique_ptr<GeneratedDeck>>
EvaluateBestDecks(const std::vector<std::unique_ptr<GeneratedDeck>> &decks,
                  const std::vector<Spell> &available_cards) {
  ThreadsafeRandom rand;
  std::vector<std::thread> threads;
  threads.reserve(decks.size());
  std::vector<std::unique_ptr<GeneratedDeck>> re_evaluated;
  re_evaluated.reserve(decks.size());
  std::mutex mutex;
  for (int i = 0; i < decks.size(); ++i) {
    // Note: this const int is necessary to avoid a silly bug where i is updated
    // for all threads!
    const int kIter = i;
    threads.emplace_back([&, kIter]() {
      auto generated = std::make_unique<GeneratedDeck>();
      generated->iteration_nr = decks[kIter]->iteration_nr;
      generated->permutation = decks[kIter]->permutation;
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
                   const std::set<int> &forced_cards) {
  std::vector<std::unique_ptr<GeneratedDeck>> all_decks;
  std::vector<std::thread> threads;
  std::mutex mutex;
  for (int i = 0; i < kThreads; ++i) {
    threads.emplace_back([&]() {
      std::unique_ptr<GeneratedDeck> more =
          GradientDescent(available_cards, forced_cards, i);

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
  for (const std::string_view cardname : available_cards) {
    const Spell *spell = FindPtrOrNull(spells_by_name, cardname);
    if (spell == nullptr) {
      FATAL << "Spell " << cardname << " is not listed in all_cards"
            << std::endl;
    }
    if (spell->cost.contains(Color::Red) ||
        spell->cost.contains(Color::Green) ||
        spell->cost.contains(Color::Blue)) {
      // This is a hack to focus on a subset of colors. Ideally the program
      // would first run a simulation to pick best colors, and then optimize
      // within the colors. Or be more aggressive about what cards to keep.
      // TODO: replace with better algorithm.
      continue;
    }
    result.push_back(*spell);
  }
  return result;
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
  for (int i = 0; i < best.size() && i < kPrintTopN; ++i) {
    const GeneratedDeck &generated = *best[i];
    std::cout << std::endl;
    std::cout << "Score: " << generated.score << std::endl;
    std::cout << "Iteration: " << generated.iteration_nr << std::endl;
    // std::cout << best[i]->param << std::endl;

    Deck deck = TournamentDeck(generated.param);
    // std::cout << deck << std::endl;
    PrintLands(deck);
    PrintContributions(deck, generated.contributions);
  }
}

void GenerateDeck(const std::vector<Spell> &available_cards,
                  const std::set<int> &forced_cards) {
  std::vector<std::unique_ptr<GeneratedDeck>> all_decks =
      RunMultipleDescent(available_cards, forced_cards);

  // TODO: Unique the decks, currently generates duplicates.
  PrintGeneratedDecksShort(all_decks);

  // Re-evaluate 8 best decks, to find the best one.
  std::vector<std::unique_ptr<GeneratedDeck>> best_decks =
      EvaluateBestDecks(all_decks, available_cards);
  PrintGeneratedDecksDetailed(available_cards, best_decks);
}

// -----------------------------------------------------------------------------

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

TEST(GeneratePermutationWithinLimits) {
  ThreadsafeRandom rand;
  std::set<int> forced_cards = {24, 27, 31};
  std::vector<int> permutation =
      GeneratePermutation(100, 23, forced_cards, rand);
  EXPECT_EQ(permutation.size(), 23);
  EXPECT_TRUE(AreInRange(permutation, 100));

  std::set<int> picked(permutation.begin(), permutation.end());
  // No duplicate
  EXPECT_EQ(picked.size(), permutation.size());
  EXPECT_TRUE(IsSubset(forced_cards, picked));
}

TEST(GeneratePermutationIgnoresForcedCardsOutOfRange) {
  ThreadsafeRandom rand;
  std::set<int> forced_cards = {1000};
  std::vector<int> permutation =
      GeneratePermutation(100, 23, forced_cards, rand);
  EXPECT_TRUE(AreInRange(permutation, 100));

  std::set<int> picked(permutation.begin(), permutation.end());
  EXPECT_FALSE(IsSubset(forced_cards, picked));
}

TEST(GeneratePermutationWhenForcedCardsAlreadyMaximum) {
  ThreadsafeRandom rand;
  std::set<int> forced_cards = {0, 1, 2};
  std::vector<int> permutation =
      GeneratePermutation(100, 3, forced_cards, rand);
  EXPECT_EQ(permutation.size(), 3);

  std::set<int> picked(permutation.begin(), permutation.end());
  EXPECT_TRUE(IsSubset(forced_cards, picked));
}

TEST(SelectCardsToReplaceRemovesLowestContribution) {
  std::vector<Spell> available_cards;
  available_cards.push_back(MakeSpell("W", 1, "Minister"));
  available_cards.push_back(MakeSpell("WW3", 1, "Invitation"));
  available_cards.push_back(MakeSpell("BB3", 1, "Security"));

  std::vector<int> permutation = {0, 1, 2};
  std::unordered_map<int, const Contribution *> permutation_to_contributions;
  CardContributions contributions = MakeContributionMaps(
      available_cards, permutation, &permutation_to_contributions);

  AddDelta(1, "Minister", &contributions);
  AddDelta(4, "Security", &contributions);
  AddDelta(6, "Invitation", &contributions);

  std::vector<int> to_replace =
      SelectCardsToReplace(permutation_to_contributions, {}, 1);
  CHECK(to_replace.size() == 1);
  // Remove lowest contribution
  EXPECT_EQ(available_cards[to_replace[0]].name, "Minister");
}

TEST(SelectCardsToReplaceRespectForcedCards) {
  std::vector<Spell> available_cards;
  available_cards.push_back(MakeSpell("W", 1, "Minister"));
  available_cards.push_back(MakeSpell("WW3", 1, "Invitation"));
  available_cards.push_back(MakeSpell("BB3", 1, "Security"));

  std::vector<int> permutation = {0, 1, 2};
  std::unordered_map<int, const Contribution *> permutation_to_contributions;
  CardContributions contributions = MakeContributionMaps(
      available_cards, permutation, &permutation_to_contributions);

  AddDelta(1, "Minister", &contributions);
  AddDelta(4, "Security", &contributions);
  AddDelta(6, "Invitation", &contributions);

  std::vector<int> to_replace =
      SelectCardsToReplace(permutation_to_contributions, {0}, 1);
  CHECK(to_replace.size() == 1);
  // Remove lowest contribution
  EXPECT_EQ(available_cards[to_replace[0]].name, "Security");
}

TEST(ReplaceBadCards) {
  ThreadsafeRandom rand;
  std::vector<int> permutation = {3, 1, 2, 0};
  std::vector<int> to_replace = {1, 2};

  std::vector<int> new_permutation =
      ReplaceBadCards(permutation, to_replace, 100, rand);
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
