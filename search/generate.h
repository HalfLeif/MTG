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

Library ApplyPermutation(const std::vector<Spell> &available_cards,
                         const std::vector<int> &permutation) {
  Library::Builder builder;
  builder.SetLimited();
  for (int index : permutation) {
    builder.AddSpell(available_cards[index]);
  }
  return builder.Build();
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

std::vector<int>
ReplaceBadCards(const std::unordered_map<int, const Contribution *>
                    &permutation_to_contributions,
                const int total, ThreadsafeRandom &rand) {
  std::vector<std::pair<double, int>> scores;
  for (const auto &[index, contribution] : permutation_to_contributions) {
    scores.emplace_back(contribution->score, index);
  }
  std::sort(scores.begin(), scores.end());

  // TODO: consider a stochastic choice here instead of always replacing bottom
  // Would produce Stochastic Gradient Descent instead of norm Gradient Descent.
  // Could also consider some decay here, instead of constant number.
  std::vector<int> new_permutation;
  new_permutation.reserve(scores.size());
  constexpr int kMinReplacePerIteration = 3;
  for (const auto &[score, index] : scores) {
    int new_index = index;
    if (
        // Replace useless card
        score <= 0 ||
        // Replace up to N bad cards
        new_permutation.size() < kMinReplacePerIteration ||
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
  Param param;
  double score;
  CardContributions contributions;
  int iteration_nr = 0;
};

void AnalyzeGeneratedDecks(std::vector<std::unique_ptr<GeneratedDeck>> decks) {
  std::sort(decks.begin(), decks.end(),
            [](const auto &a, const auto &b) { return a->score > b->score; });
  for (int i = 0; i < decks.size() && i < 10; ++i) {
    std::cout << decks[i]->score << " iteration " << decks[i]->iteration_nr
              << std::endl;
  }
}

std::vector<std::unique_ptr<GeneratedDeck>>
GradientDescent(const std::vector<Spell> &available_cards,
                ThreadsafeRandom &rand) {
  // Keep track of best permutations.
  std::vector<std::unique_ptr<GeneratedDeck>> iterations;

  // 1. Create a random starting deck.
  // Limited: 23 spells, 17 lands.
  std::vector<int> permutation =
      GeneratePermutation(available_cards.size(), 23, rand);

  for (int i = 0; i < 50; ++i) {
    auto generated = std::make_unique<GeneratedDeck>();
    generated->iteration_nr = i;

    // 2. Find best land distribution for small number of iterations.
    Library lib = ApplyPermutation(available_cards, permutation);
    generated->param = CompareParams(lib, 15, false);

    // 3. Track contributions per card.
    std::unordered_map<int, const Contribution *> permutation_to_contributions;
    generated->contributions = MakeContributionMaps(
        available_cards, permutation, permutation_to_contributions);
    generated->score =
        RunParam(lib, generated->param, 50, &generated->contributions);

    // 4. Replace bad cards for next iteration.
    generated->permutation = std::move(permutation);
    permutation = ReplaceBadCards(permutation_to_contributions,
                                  available_cards.size(), rand);
    iterations.push_back(std::move(generated));
  }

  return iterations;
}

void GenerateDeck(const std::vector<Spell> &available_cards) {
  ThreadsafeRandom rand;
  std::vector<std::unique_ptr<GeneratedDeck>> all_decks;
  std::vector<std::thread> threads;
  std::mutex mutex;
  for (int i = 0; i < 8; ++i) {
    threads.emplace_back([&]() {
      std::vector<std::unique_ptr<GeneratedDeck>> more =
          GradientDescent(available_cards, rand);

      MutexLock lock(&mutex);
      std::move(more.begin(), more.end(), std::back_inserter(all_decks));
    });
  }
  for (std::thread &thread : threads) {
    thread.join();
  }
  AnalyzeGeneratedDecks(std::move(all_decks));
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
