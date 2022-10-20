#pragma once

#include <cstdio>
#include <string_view>
#include <vector>

#include "../core/sealed_deck.h"

std::vector<Spell> MakeFakeCards() {
  std::vector<Spell> all_cards;
  constexpr int kMinMana = 1;
  constexpr int kMaxMana = 7;

  constexpr int kBuffSize = 10;
  char buffer[kBuffSize];
  for (int i = kMinMana; i <= kMaxMana; ++i) {
    int write_size = snprintf(buffer, kBuffSize, "W%d", i - 1);
    CHECK(write_size >= 0 && write_size < kBuffSize);
    all_cards.push_back(MakeSpell(buffer, 1, buffer));
  }
  return all_cards;
}

// Creates a set of copies of various mana costs for analyzing the perfect mana
// curve.
class Fake : public SealedDeck {
public:
  Fake() {
    all_cards_ = MakeFakeCards();
    constexpr int kCopies = 12;
    for (const Spell &spell : all_cards_) {
      for (int c = 0; c < kCopies; ++c) {
        all_copies_.push_back(spell.name);
      }
    }
  }

  const std::vector<Spell> &all_cards() const { return all_cards_; }

  // All cards that were opened in this SealedDeck tournament.
  std::vector<std::string_view> cards() const override { return all_copies_; }

  std::string_view data_path() const override {
    FATAL << "Attempted to read fake card file.";
    return "";
  }
  int MaxColors() const override { return 1; }
  std::vector<Color> AvailableColors() const override { return {Color::White}; }

private:
  std::vector<Spell> all_cards_;
  std::vector<std::string_view> all_copies_;
};

/*
Score: 78.2322
Iteration: 132
Lands { W=16 }
    2595 W0 (W)
    3276 W1 (W1)
    3276 W1 (W1)
    3276 W1 (W1)
    3276 W1 (W1)
    3276 W1 (W1)
    3276 W1 (W1)
    3609 W5 (W5)
    3609 W5 (W5)
    4063 W2 (W2)
    4063 W2 (W2)
    4063 W2 (W2)
    4063 W2 (W2)
    4063 W2 (W2)
    4063 W2 (W2)
    4416 W3 (W3)
    4416 W3 (W3)
    4416 W3 (W3)
    4416 W3 (W3)
    4416 W3 (W3)
    4416 W3 (W3)
    4582 W4 (W4)
    4582 W4 (W4)
    4582 W4 (W4)

*/
