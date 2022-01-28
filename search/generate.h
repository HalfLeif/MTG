#include <algorithm>
#include <memory>
#include <mutex>
#include <numeric>
#include <random>
#include <thread>
#include <unordered_map>
#include <vector>

#include "../core/collection.h"
#include "../core/contribution.h"
#include "../core/debug.h"
#include "../core/library.h"
#include "../core/random.h"
#include "../core/spell.h"
#include "search.h"

// Params at top in order to quickly reduce for debugging purposes.

// Number of threads determines how many gradient descents will run in parallel.
constexpr int kThreads = 8;
constexpr int kDescentDepth = 125;
constexpr int kPrintTopN = 3;

// LandSearch determines how many iterations are spent to optimize the land
// distribution for a particular deck. Games on the other hand is used to
// specify for how many games a deck should be evaluated, using the optimal land
// distribution.
// constexpr int kFastLandSearch = 15;
// constexpr int kFastGames = 75;
//
// constexpr int kDeepLandSearch = 75;
// constexpr int kDeepGames = 500;

constexpr int kFastLandSearch = 10;
constexpr int kFastGames = 5;

constexpr int kDeepLandSearch = 7;
constexpr int kDeepGames = 50;

std::vector<int> GeneratePermutation(const int total, const int wanted,
                                     ThreadsafeRandom &rand) {
  std::vector<int> permutation;
  if (wanted > total) {
    ERROR << "Cannot request more cards than there are.\n";
    return permutation;
  }

  permutation.resize(total);
  std::iota(permutation.begin(), permutation.end(), 0);
  rand.Shuffle(permutation);
  permutation.resize(wanted);
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

  // Note: this is a hack since generating decks doesn't take lands into
  // account.
  // This is for Voldaren Estate.
  // TODO: Support non-basic lands properly.
  builder.AddLand(BasicLand(Color::Colorless));

  return builder.BuildUnique();
}

// MutationRate is high for low-value cards,  and less for good cards.
double MutationRate(int order, int total) {
  constexpr double kMax = 0.10;
  constexpr double kMin = 0.0;
  const double slope = (kMin - kMax) / total;
  return kMax + order * slope;
}

// Returns whether should mutate this card.
bool MutateCard(int order, int total, ThreadsafeRandom &rand) {
  // Seems like mutations don't help.
  return false;
  double r = rand.RandOne();
  return r < MutationRate(order, total);
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
ReplaceBadCards(const std::unordered_map<int, const Contribution *>
                    &permutation_to_contributions,
                const int total, const int iteration_nr,
                ThreadsafeRandom &rand) {
  std::vector<std::pair<double, int>> scores;
  for (const auto &[index, contribution] : permutation_to_contributions) {
    scores.emplace_back(contribution->GetContribution(), index);
  }
  std::sort(scores.begin(), scores.end());

  // Could also consider some decay here, instead of constant number.
  std::vector<int> new_permutation;
  new_permutation.reserve(scores.size());
  const int min_replace = NumReplace(iteration_nr);
  for (const auto &[score, index] : scores) {
    int new_index = index;
    if (
        // Replace useless card
        score <= 0 ||
        // Replace up to N bad cards
        new_permutation.size() < min_replace ||
        // Maybe replace card randomly, higher chance for bad cards.
        MutateCard(new_permutation.size(), permutation_to_contributions.size(),
                   rand)) {
      // Choose a different card randonly.
      while (ContainsKey(permutation_to_contributions, new_index) ||
             ContainsItem(new_permutation, new_index)) {
        new_index = rand.Rand() % total;
      }
    }
    new_permutation.push_back(new_index);
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

void PrintTopGeneratedDecks(
    const std::vector<std::unique_ptr<GeneratedDeck>> &decks) {
  for (int i = 0; i < decks.size() && i < 10; ++i) {
    std::cout << decks[i]->score << " iteration " << decks[i]->iteration_nr
              << std::endl;
  }
}

// Only return the best one. That way gets more diversity between best N decks.
std::unique_ptr<GeneratedDeck>
GradientDescent(const std::vector<Spell> &available_cards,
                ThreadsafeRandom &rand) {
  // Keep track of best permutations.
  std::vector<std::unique_ptr<GeneratedDeck>> iterations;

  // 1. Create a random starting deck.
  // Limited: 23 spells, 17 lands.
  std::vector<int> permutation =
      GeneratePermutation(available_cards.size(), 23, rand);

  for (int i = 0; i < kDescentDepth; ++i) {
    auto generated = std::make_unique<GeneratedDeck>();
    generated->iteration_nr = i;

    // 2. Find best land distribution for small number of iterations.
    generated->lib = ApplyPermutation(available_cards, permutation);
    generated->param = CompareParams(*generated->lib, kFastLandSearch, false);

    // 3. Track contributions per card.
    std::unordered_map<int, const Contribution *> permutation_to_contributions;
    generated->contributions = MakeContributionMaps(
        available_cards, permutation, &permutation_to_contributions);
    generated->score = RunParam(*generated->lib, generated->param, kFastGames,
                                &generated->contributions);

    // 4. Replace bad cards for next iteration.
    generated->permutation = std::move(permutation);
    permutation = ReplaceBadCards(permutation_to_contributions,
                                  available_cards.size(), i, rand);
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
      generated->param = CompareParams(*generated->lib, kDeepLandSearch, false);
      generated->score = RunParam(*generated->lib, generated->param, kDeepGames,
                                  &generated->contributions);

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
GenerateEarlyDecks(const std::vector<Spell> &available_cards) {
  ThreadsafeRandom rand;
  std::vector<std::unique_ptr<GeneratedDeck>> all_decks;
  std::vector<std::thread> threads;
  std::mutex mutex;
  for (int i = 0; i < kThreads; ++i) {
    threads.emplace_back([&]() {
      std::unique_ptr<GeneratedDeck> more =
          GradientDescent(available_cards, rand);

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
    auto it = spells_by_name.find(cardname);
    if (it == spells_by_name.end()) {
      ERROR << "Spell " << cardname << " is not listed in all_cards"
            << std::endl;
      exit(1);
    }
    const Spell &spell = *it->second;
    if (ContainsKey(spell.cost, Color::Red) ||
        ContainsKey(spell.cost, Color::Green) ||
        ContainsKey(spell.cost, Color::Blue)) {
      // This is a hack to focus on a subset of colors. Ideally the program
      // would first run a simulation to pick best colors, and the optimize
      // within the colors. Or be more aggressive about what cards to keep.
      // TODO: replace with better algorithm.
      continue;
    }
    result.push_back(spell);
  }
  return result;
}

void GenerateDeck(const std::vector<Spell> &available_cards) {
  std::vector<std::unique_ptr<GeneratedDeck>> all_decks =
      GenerateEarlyDecks(available_cards);

  // TODO: Unique the decks, currently generates duplicates.
  PrintTopGeneratedDecks(all_decks);

  // Re-evaluate 8 best decks, to find the best one.
  std::vector<std::unique_ptr<GeneratedDeck>> best =
      EvaluateBestDecks(all_decks, available_cards);
  std::cout << "\nFound the best generated decks! " << std::endl;
  for (int i = 0; i < best.size() && i < kPrintTopN; ++i) {
    std::cout << std::endl;
    std::cout << "Score: " << best[i]->score << std::endl;
    std::cout << "Iteration: " << best[i]->iteration_nr << std::endl;
    std::cout << best[i]->param << std::endl;
    PrintContributions(best[i]->contributions);
  }
}

// -----------------------------------------------------------------------------

TEST(MutationRate) {
  double bad = MutationRate(5, 23);
  EXPECT_LT(0.05, bad);
  EXPECT_LT(bad, 0.10);

  double good = MutationRate(20, 23);
  EXPECT_LT(0.00, good);
  EXPECT_LT(good, 0.04);
}
