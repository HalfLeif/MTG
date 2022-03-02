#pragma once

#include <string_view>
#include <vector>

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
};
