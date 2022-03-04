#pragma once

#include <string_view>
#include <vector>

#include "mana.h"

class SealedDeck {
public:
  // Path to csv file with card information for this expansion.
  virtual std::string_view data_path() const = 0;

  // All cards that were opened in this SealedDeck tournament.
  virtual std::vector<std::string_view> cards() const = 0;

  // Cards among opened cards that are manually forced in the deck during deck
  // generation.
  virtual std::vector<std::string_view> forced_cards() const { return {}; }

  // Resulting deck (for analysis purposes).
  virtual std::vector<std::string_view> chosen_deck() const { return {}; };

  // Minimum number of colors in generated deck.
  virtual int MinColors() const { return 1; }

  // Maximum number of colors in generated deck.
  virtual int MaxColors() const { return 3; }

  // Colors the generator can use for building a deck.
  virtual std::vector<Color> AvailableColors() const {
    return {Color::Black, Color::White, Color::Green, Color::Blue, Color::Red};
  }

  // Returns vector of all color combinations from 1-3 distinct colors, based on
  // kAvailableColors.
  const std::vector<ManaCost> &ColorCombinations() {
    const std::vector<ManaCost> *kCombinations = [this]() {
      std::vector<ManaCost> *combinations = new std::vector<ManaCost>();
      GenerateAllColorCombinations(this->AvailableColors(), this->MinColors(),
                                   this->MaxColors(), combinations);
      return combinations;
    }();
    return *kCombinations;
  }
};
