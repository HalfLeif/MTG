#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "common/benchmark.h"
#include "common/test.h"
#include "core/benchmarks.h"
#include "core/library.h"
#include "core/sealed_deck.h"
#include "decks/bolas.h"
#include "decks/bro.h"
#include "decks/dmu.h"
#include "decks/dnd.h"
#include "decks/eld.h"
#include "decks/fake.h"
#include "decks/m20.h"
#include "decks/mid.h"
#include "decks/mom.h"
#include "decks/neo.h"
#include "decks/snc.h"
#include "decks/thb.h"
#include "decks/vow.h"
#include "parser/parse_csv.h"
#include "search/generate.h"
#include "search/task.h"

constexpr bool DEBUG_ON = false;
constexpr bool PARANOIA = true;

void OptimizeLands(const Library &lib) {
  ThreadsafeRandom random(/*seed=*/21);
  CompareParams(lib, random, 2000);
}

void GenerateDeck(const std::vector<Spell> &all_cards, SealedDeck *sealed) {
  std::vector<Spell> available_cards = FilterCards(all_cards, sealed->cards());
  auto forced_cards = FindForcedCards(available_cards, sealed->forced_cards());
  GenerateDeck(available_cards, forced_cards, sealed->ColorCombinations());
}

void OptimizeDeck(const std::vector<Spell> &all_cards,
                  const SealedDeck *sealed) {
  std::vector<Spell> chosen_cards =
      FilterCards(all_cards, sealed->chosen_deck());
  std::vector<Spell> base_cards = FilterCards(all_cards, {
                                                             "InvasionofLorwyn",
                                                         });
  std::vector<Spell> exp_cards =
      FilterCards(all_cards, {
                                 "AtraxaPraetorsVoice",
                             });

  Library lib = Library::Builder()
                    .SetLimited()
                    .AddSpells(chosen_cards)
                    .AddSpells(base_cards, Experiment::base)
                    .AddSpells(exp_cards, Experiment::exp)
                    .AddLand(TapLand("WG"))
                    .AddLand(TapLand("UG"), Experiment::exp)
                    .Build();

  OptimizeLands(lib);
}

int main(int argc, char *argv[]) {
  std::cout << "\n -- Running tests --\n";
  RunAllTests();
  std::cout << "\n -- Started program --\n";
  // RunAllBenchmarks();

  auto sealed = std::make_unique<Mom>();
  std::vector<Spell> all_cards = ReadCards(std::string(sealed->data_path()));

  // GenerateDeck(all_cards, sealed.get());
  OptimizeDeck(all_cards, sealed.get());
  // OptimizeLands(kDMU);

  return 0;
}
