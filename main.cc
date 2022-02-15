#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "common/benchmark.h"
#include "common/test.h"
#include "core/benchmarks.h"
#include "core/library.h"
#include "decks/bolas.h"
#include "decks/dnd.h"
#include "decks/eld.h"
#include "decks/m20.h"
#include "decks/mid.h"
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
constexpr bool PARANOIA = false;

int main(int argc, char *argv[]) {
  std::cout << "\n -- Running tests --\n";
  RunAllTests();
  std::cout << "\n -- Started program --\n";
  // RunAllBenchmarks();

  std::vector<Spell> all_cards = ReadCards("data/vow/cards.csv");
  // std::vector<Spell> available_cards = FilterCards(all_cards, VowCards());
  // auto forced_cards = FindForcedCards(available_cards, VowForcedCards());
  // GenerateDeck(available_cards, forced_cards);

  // const Library &lib = GetMainLib();
  std::vector<Spell> chosen_cards = FilterCards(all_cards, VowDeck());
  std::vector<Spell> exp_cards =
      FilterCards(all_cards, {"Sigarda's Imprisonment"});

  Library lib = Library::Builder()
                    .SetLimited()
                    .AddSpells(chosen_cards)
                    .AddSpells(exp_cards, Experiment::exp)
                    .AddLand(BasicLand(Color::Colorless))
                    .Build();

  ThreadsafeRandom random;
  CompareParams(lib, random, 1000);

  return 0;
}
