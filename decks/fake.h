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
  all_cards.push_back(MakeSpell("W", 0, "SmallTrick"));
  all_cards.push_back(MakeSpell("W1", 0, "Trick"));
  all_cards.push_back(MakeSpell("WW1", 0, "BigTrick"));
  return all_cards;
}

// Creates a set of copies of various mana costs for analyzing the perfect mana
// curve.
class Fake : public SealedDeck {
public:
  Fake() {
    all_cards_ = MakeFakeCards();
    constexpr int kCopies = 8;
    for (const Spell &spell : all_cards_) {
      for (int c = 0; c < kCopies; ++c) {
        all_copies_.push_back(spell.name);
      }
    }
  }

  const std::vector<Spell> &all_cards() const { return all_cards_; }

  // All cards that were opened in this SealedDeck tournament.
  std::vector<std::string_view> cards() const override { return all_copies_; }

  // Cards among opened cards that are manually forced in the deck during deck
  // generation.
  std::vector<std::string_view> forced_cards() const override {
    return {
        "Trick",
        "Trick",
        "BigTrick",
    };
  }

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
10 turns

Score: 93.1 (108.4 - 15.2)
Iteration: 70
Lands { W=17 }
    3016 Trick (W1)
    3016 Trick (W1)
    3229 W0 (W)
    3580 W6 (W6)
    4114 W1 (W1)
    4114 W1 (W1)
    4114 W1 (W1)
    4223 BigTrick (WW1)
    4864 W2 (W2)
    4864 W2 (W2)
    4864 W2 (W2)
    4864 W2 (W2)
    4864 W2 (W2)
    5916 W3 (W3)
    5916 W3 (W3)
    5916 W3 (W3)
    5916 W3 (W3)
    5916 W3 (W3)
    5916 W3 (W3)
    6017 W5 (W5)
    6066 W4 (W4)
    6066 W4 (W4)
    6066 W4 (W4)

*/
