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
#include "decks/dnd.h"
#include "decks/eld.h"
#include "decks/m20.h"
#include "decks/mid.h"
#include "decks/neo.h"
#include "decks/snc.h"
#include "decks/thb.h"
#include "decks/vow.h"
#include "parser/parse_csv.h"
#include "search/generate.h"
#include "search/task.h"

const Library &GetMainLib() {
  // return kELD;
  // return kM20;
  // return kTHB;
  // return kBolas;
  // return kDND;
  return kMID;
}

constexpr bool DEBUG_ON = false;
constexpr bool PARANOIA = true; // TODO

int main(int argc, char *argv[]) {
  std::cout << "\n -- Running tests --\n";
  RunAllTests();
  std::cout << "\n -- Started program --\n";
  // RunAllBenchmarks();

  std::unique_ptr<SealedDeck> sealed = std::make_unique<Snc>();
  std::vector<Spell> all_cards = ReadCards(std::string(sealed->data_path()));

  std::vector<Spell> available_cards = FilterCards(all_cards, sealed->cards());
  auto forced_cards = FindForcedCards(available_cards, sealed->forced_cards());

  // DEBUG
  // int forced = *forced_cards.begin();
  // std::cout << "Forced card: " << available_cards[forced] << "\n";
  // GenerateDeck(available_cards, forced_cards, sealed->ColorCombinations());

  std::vector<Spell> chosen_cards =
      FilterCards(all_cards, sealed->chosen_deck());
  std::vector<Spell> base_cards = FilterCards(all_cards, {
                                                             // "Wrecking Crew",
                                                         });
  std::vector<Spell> exp_cards =
      FilterCards(all_cards, {
                                 // "Park Heights Pegasus",
                                 // "Sky Crier",
                             });

  Library lib = Library::Builder()
                    .SetLimited()
                    .AddSpells(chosen_cards)
                    .AddSpells(base_cards, Experiment::base)
                    .AddSpells(exp_cards, Experiment::exp)
                    .AddLand(DualLand(Color::Green, Color::White))
                    .AddLand(FetchLand())
                    .AddLand(FetchLand())
                    .Build();

  ThreadsafeRandom random;
  CompareParams(lib, random, 1000);

  return 0;
}
