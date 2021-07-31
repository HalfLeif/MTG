#pragma once

#include "../core/data.h"

class ELD : public Format {
public:
  static const Format &Instance() {
    static const auto *const kInstance = new ELD;
    return *kInstance;
  }

  Color PrimaryColor() const override { return Color::Red; }
  Color SecondaryColor() const override { return Color::Blue; }

  Deck TournamentCards(Experiment experiment) const override {
    Deck deck;
    // AddN(deck.cards, 1, MakeCard("1R", 1, "CrystalSlipper"));

    if (experiment == Experiment::exp) { // Adamant
      AddN(deck.cards, 1, MakeCard("RRR", 1, "Clockwork"));
      AddN(deck.cards, 1, MakeCard("1RRR", 1, "EmberethPaladin"));
      AddN(deck.cards, 1, MakeCard("2RRR", 1, "SearingBarrage"));
      AddN(deck.cards, 1, MakeCard("2UUU", 1, "UnexplainedVision"));

    } else {
      AddN(deck.cards, 1, MakeCard("3", 1, "Clockwork"));
      AddN(deck.cards, 1, MakeCard("3R", 1, "EmberethPaladin"));
      AddN(deck.cards, 1, MakeCard("4R", 1, "SearingBarrage"));
      AddN(deck.cards, 1, MakeCard("4U", 1, "UnexplainedVision"));
    }

    AddN(deck.cards, 1, MakeCard("R", 1, "FerventChampion"));
    AddN(deck.cards, 1, MakeCard("1", 1, "ScaldingCauldron"));
    AddN(deck.cards, 1, MakeCard("U", 1, "WishingWell"));

    AddN(deck.cards, 1, MakeCard("1R", 1, "RimrockKnight"));
    AddN(deck.cards, 1, MakeCard("1R", 2, "Robber"));
    AddN(deck.cards, 1, MakeCard("1U", 2, "Faerie"));
    AddN(deck.cards, 2, MakeCard("1R", 0, "Dragonfire"));
    AddN(deck.cards, 1, MakeCard("1R", 0, "Fling"));
    AddN(deck.cards, 1, MakeCard("1U", 1, "Alliance"));

    AddN(deck.cards, 1, MakeCard("2U", 1, "QueenOfIce"));
    AddN(deck.cards, 1, MakeCard("2R", 1, "Trebuchet"));
    AddN(deck.cards, 1, MakeCard("2R", 3, "Pyromancer"));
    AddN(deck.cards, 1, MakeCard("2R", 0, "BlowYourHouseDown"));

    AddN(deck.cards, 1, MakeCard("4", 1, "LochDragon"));
    AddN(deck.cards, 1, MakeCard("3R", 1, "OgreErrant"));
    AddN(deck.cards, 2, MakeCard("3R", 1, "SkullknockerOgre"));

    AddN(deck.cards, 1, MakeCard("4U", 2, "SageOfTheFalls"));

    return deck;
  }
};
