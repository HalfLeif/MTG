#pragma once

#include "deck.h"
#include "library.h"
#include "param.h"

void FillLands(const Param &param, Deck *deck) {
  AddN(deck->lands, param.primary, BasicLand(param.lib->PrimaryColor()));
  AddN(deck->lands, param.secondary, BasicLand(param.lib->SecondaryColor()));
  AddN(deck->lands, param.tertiary, BasicLand(param.lib->TertiaryColor()));
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
                    int tertiary = 0) {
  return TournamentDeck({.lib = &lib,
                         .experiment = experiment,
                         .secondary = secondary,
                         .tertiary = tertiary});
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

// -----------------------------------------------------------------------------

TEST(TournamentDeckWithFewerSpells) {
  Library::Builder builder;
  const int num_spells = TotalSpells(DeckSize::limited) - 1;
  for (int i = 0; i < num_spells; ++i) {
    if (i % 2 == 0) {
      builder.AddSpell(MakeSpell("B2"));
    } else {
      builder.AddSpell(MakeSpell("W3"));
    }
  }
  Library lib = builder.Build();

  Param param = {
      .lib = &lib,
      .primary = 10,
      .secondary = 8,
  };
  Deck deck = TournamentDeck(param);
  EXPECT_EQ(deck.spells.size(), 22);
  EXPECT_EQ(deck.lands.size(), 18);
  EXPECT_EQ(deck.Size(), TotalCards(DeckSize::limited));
}
