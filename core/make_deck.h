#pragma once

#include "deck.h"
#include "library.h"

struct Param {
  Experiment experiment = Experiment::base;
  int secondary = 0;
  int ternary = 0;
  DeckSize deck_size = DeckSize::limited;
};

std::ostream &operator<<(std::ostream &stream, const Param &param) {
  stream << "Param experiment: " << param.experiment;
  // Note: This is an approximation since must also take into account number of
  // non-basic lands!
  const int primary_lands =
      TotalLands(param.deck_size) - param.secondary - param.ternary;
  stream << "  " << GetFormat().PrimaryColor() << "=" << primary_lands << "^";
  if (param.secondary > 0) {
    stream << "  " << GetFormat().SecondaryColor() << "=" << param.secondary;
  }
  if (param.ternary > 0) {
    stream << "  " << GetFormat().TernaryColor() << "=" << param.ternary;
  }
  return stream;
}

void FillLands(const Param &param, Deck *deck) {
  AddN(deck->lands, param.secondary, BasicLand(GetFormat().SecondaryColor()));
  AddN(deck->lands, param.ternary, BasicLand(GetFormat().TernaryColor()));

  int total = deck->lands.size() + deck->spells.size();
  int expected = TotalCards(param.deck_size);
  if (total < expected) {
    AddN(deck->lands, expected - total, BasicLand(GetFormat().PrimaryColor()));
  }
}

Deck TournamentDeck(const Param &param) {
  Deck deck = GetFormat().MakeDeck(param.experiment);
  if (deck.spells.size() != TotalSpells(param.deck_size)) {
    ERROR << "Deck spells: " << deck.spells.size() << " for " << param << "\n";
  }

  FillLands(param, &deck);
  if (deck.lands.size() != TotalLands(param.deck_size)) {
    ERROR << "Deck lands: " << deck.lands.size() << " for " << param << "\n";
  }
  return deck;
}

Deck TournamentDeck(Experiment experiment, int secondary, int ternary = 0) {
  return TournamentDeck(
      {.experiment = experiment, .secondary = secondary, .ternary = ternary});
}

Deck TestDeck() {
  Deck deck;
  AddN(deck.spells, 10, MakeSpell("1B"));
  AddN(deck.spells, 10, MakeSpell("1W"));
  deck.spells.push_back(MakeSpell("WB"));
  deck.spells.push_back(MakeSpell("1BB"));
  deck.spells.push_back(MakeSpell("3BB"));

  AddN(deck.lands, 8, BasicLand(Color::White));
  AddN(deck.lands, 8, BasicLand(Color::Black));
  AddN(deck.lands, 1, FetchLand());
  return deck;
}
