#pragma once

#include "deck.h"
#include "mana.h"

struct Player {
  Deck library;
  Deck hand;
  Deck battlefield;
  Deck graveyard;
};

struct TurnState {
  ManaCost mana_pool;
  ManaCost agg_card_cost;
};

enum class Experiment : int {
  always, // always included.
  base,
  exp,
};

std::ostream &operator<<(std::ostream &stream, const Experiment &experiment) {
  switch (experiment) {
  case Experiment::always:
    break;
  case Experiment::base:
    stream << "base";
    break;
  case Experiment::exp:
    stream << "exp";
    break;
  }
  return stream;
}

class Format {
public:
  virtual Deck TournamentCards(Experiment experiment) const = 0;
  virtual Color PrimaryColor() const = 0;
  virtual Color SecondaryColor() const = 0;
  virtual Color TernaryColor() const { return Color::Colorless; };
  virtual DeckSize GetDeckSize() const { return DeckSize::limited; };
};

const Format &GetFormat();
