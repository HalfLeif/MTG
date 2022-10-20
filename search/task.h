#pragma once

#include "../common/random.h"
#include "../core/deck.h"
#include "../core/game_logic.h"
#include "../core/library.h"
#include "search.h"

void StepOne() {
  Spell card = MakeSpell("3WBWB");
  INFO << card;
}

void StepTwo() {
  ThreadsafeRandom rand;
  Library lib = TestLibrary();
  Deck deck = TournamentDeck(lib, Experiment::base, 6);
  INFO << deck;
  int score = PlayGame(lib, deck, NoStrategy, 5, rand);
  std::cout << "Game score: " << score << "\n";
}

void StepThree() {
  ThreadsafeRandom rand;
  Library lib = TestLibrary();
  Deck deck = TournamentDeck(lib, Experiment::base, 6);
  INFO << deck;
  Metrics score = AverageScore(lib, deck, SimpleStrategy, 7, 100, rand);
  std::cout << "Game score: " << score << "\n";
}

void CompareStrategies() {
  ThreadsafeRandom rand;
  Library lib = TestLibrary();
  Deck deck = TournamentDeck(lib, Experiment::base, 6);
  {
    Metrics score = AverageScore(lib, deck, NoStrategy, 8, 100, rand);
    std::cout << "NoStrategy score: " << score << "\n";
  }
  {
    Metrics score = AverageScore(lib, deck, SimpleStrategy, 8, 100, rand);
    std::cout << "SimpleStrategy score: " << score << "\n";
  }
}
