#pragma once

#include "deck.h"
#include "library.h"

struct Param {
  const Library *lib;
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
  stream << "  " << param.lib->PrimaryColor() << "=" << primary_lands;
  if (param.secondary > 0) {
    stream << "  " << param.lib->SecondaryColor() << "=" << param.secondary;
  }
  if (param.ternary > 0) {
    stream << "  " << param.lib->TernaryColor() << "=" << param.ternary;
  }
  return stream;
}

void FillLands(const Param &param, Deck *deck) {
  AddN(deck->lands, param.secondary, BasicLand(param.lib->SecondaryColor()));
  AddN(deck->lands, param.ternary, BasicLand(param.lib->TernaryColor()));

  int total = deck->lands.size() + deck->spells.size();
  int expected = TotalCards(param.deck_size);
  if (total < expected) {
    AddN(deck->lands, expected - total, BasicLand(param.lib->PrimaryColor()));
  }
}

Deck TournamentDeck(const Param &param) {
  Deck deck = param.lib->MakeDeck(param.experiment);
  if (deck.spells.size() != TotalSpells(param.deck_size)) {
    INFO << "Deck spells: " << deck.spells.size() << " for " << param << "\n";
  }

  FillLands(param, &deck);
  if (deck.lands.size() != TotalLands(param.deck_size)) {
    INFO << "Deck lands: " << deck.lands.size() << " for " << param << "\n";
  }
  return deck;
}

Deck TournamentDeck(const Library &lib, Experiment experiment, int secondary,
                    int ternary = 0) {
  return TournamentDeck({.lib = &lib,
                         .experiment = experiment,
                         .secondary = secondary,
                         .ternary = ternary});
}

Library TestLibrary() {
  auto builder = Library::Builder();
  for (int i = 0; i < 10; ++i) {
    builder.AddSpell(MakeSpell("1B"));
    builder.AddSpell(MakeSpell("1W"));
  }
  builder.AddSpell(MakeSpell("WB"));
  builder.AddSpell(MakeSpell("1BB"));
  builder.AddSpell(MakeSpell("3BB"));
  return builder.Build();
}
