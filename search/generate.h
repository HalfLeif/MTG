#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

#include "../core/collection.h"
#include "../core/debug.h"
#include "../core/library.h"
#include "../core/spell.h"
#include "search.h"

// TODO: also update the original vector, to avoid repicking on later iterations
Library GenerateRandomDeck(const std::vector<Spell> &available_cards) {
  Library::Builder builder;

  // Limited: 23 spells, 17 lands.
  constexpr int num_wanted = 23;
  builder.SetLimited();

  if (num_wanted > available_cards.size()) {
    ERROR << "Cannot request more cards than there are.\n";
    return builder.Build();
  }

  std::vector<int> permutation(available_cards.size());
  std::iota(permutation.begin(), permutation.end(), 0);

  // TODO: maybe reuse?
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(permutation.begin(), permutation.end(), g);

  result.reserve(num_wanted);
  for (int i = 0; i < num_wanted; ++i) {
    builder.AddSpell(available_cards[permutation[i]]);
  }
  return builder.Build();
}

void GenerateDeck(std::vector<Spell> available_cards) {
  // 1. Create a random starting deck.
  Library lib = GenerateRandomDeck(available_cards);
  // 2. Find best land distribution for small number of iterations.
  Param param = CompareParams(lib, 15);
  // 3. Track contributions per card.
  // TODO
}
