#pragma once

#include "../core/data.h"
#include "../core/game_logic.h"
#include "deck.h"
#include "search.h"

void StepOne() {
  Card card = MakeCard("3WBWB");
  INFO << card;
}

void StepTwo() {
  // Deck deck = TestDeck();
  Deck deck = TournamentDeck(Experiment::base, 6);
  INFO << deck;
  int score = PlayGame(deck, NoStrategy, 5);
  std::cout << "Game score: " << score << "\n";
}

void StepThree() {
  // Deck deck = TestDeck();
  Deck deck = TournamentDeck(Experiment::base, 6);
  INFO << deck;
  float score = AverageScore(deck, SimpleStrategy, 7, 100);
  std::cout << "Game score: " << score << "\n";
}

void RunBruteForceSearch() {
  // Search for the optimal land distribution!
  BruteForce(10);
}

void CompareStrategies() {
  Deck deck = TestDeck();
  {
    srand(5);
    float score = AverageScore(deck, NoStrategy, 8, 100);
    std::cout << "NoStrategy score: " << score << "\n";
  }
  {
    srand(5);
    float score = AverageScore(deck, SimpleStrategy, 8, 100);
    std::cout << "SimpleStrategy score: " << score << "\n";
  }
}
