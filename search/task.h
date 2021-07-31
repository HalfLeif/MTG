#pragma once

#include "../core/deck.h"
#include "../core/game_logic.h"
#include "../core/library.h"
#include "search.h"

void StepOne() {
  Spell card = MakeSpell("3WBWB");
  INFO << card;
}

void StepTwo() {
  Library lib = TestLibrary();
  Deck deck = TournamentDeck(lib, Experiment::base, 6);
  INFO << deck;
  int score = PlayGame(lib, deck, NoStrategy, 5);
  std::cout << "Game score: " << score << "\n";
}

void StepThree() {
  Library lib = TestLibrary();
  Deck deck = TournamentDeck(lib, Experiment::base, 6);
  INFO << deck;
  float score = AverageScore(lib, deck, SimpleStrategy, 7, 100);
  std::cout << "Game score: " << score << "\n";
}

void RunBruteForceSearch(const Library &lib) {
  // Search for the optimal land distribution!
  BruteForce(lib, 10);
}

void CompareStrategies() {
  Library lib = TestLibrary();
  Deck deck = TournamentDeck(lib, Experiment::base, 6);
  {
    srand(5);
    float score = AverageScore(lib, deck, NoStrategy, 8, 100);
    std::cout << "NoStrategy score: " << score << "\n";
  }
  {
    srand(5);
    float score = AverageScore(lib, deck, SimpleStrategy, 8, 100);
    std::cout << "SimpleStrategy score: " << score << "\n";
  }
}
