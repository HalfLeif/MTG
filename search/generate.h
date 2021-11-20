#include <algorithm>
#include <memory>
#include <numeric>
#include <random>
#include <unordered_map>
#include <vector>

#include "../core/collection.h"
#include "../core/contribution.h"
#include "../core/debug.h"
#include "../core/library.h"
#include "../core/spell.h"
#include "search.h"

std::vector<int> GeneratePermutation(const int total, const int wanted) {
  std::vector<int> permutation;
  if (wanted > total) {
    ERROR << "Cannot request more cards than there are.\n";
    return permutation;
  }

  permutation.resize(total);
  std::iota(permutation.begin(), permutation.end(), 0);

  // TODO: maybe reuse random across instances?
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(permutation.begin(), permutation.end(), g);
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

void GenerateDeck(const std::vector<Spell> &available_cards) {
  // 1. Create a random starting deck.
  // Limited: 23 spells, 17 lands.
  std::vector<int> permutation =
      GeneratePermutation(available_cards.size(), 23);

  { // TODO: Loop this for several permutations...
    std::unordered_map<int, const Contribution *> permutation_to_contributions;
    CardContributions contributions = MakeContributionMaps(
        available_cards, permutation, permutation_to_contributions);

    Library lib = ApplyPermutation(available_cards, permutation);
    // 2. Find best land distribution for small number of iterations.
    Param param = CompareParams(lib, 15);
    // 3. Track contributions per card.
    double score = RunParam(lib, param, 50, &contributions);
  }
}
