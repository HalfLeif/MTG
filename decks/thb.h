#pragma once

#include "../core/data.h"

Land Shore() {
  return {
      .type = LandType::shore,
      .color = Color::Colorless,
  };
}

class THB : public Format {
public:
  static const Format &Instance() {
    static const auto *const kInstance = new THB;
    return *kInstance;
  }

  Color PrimaryColor() const override { return Color::Green; }
  Color SecondaryColor() const override { return Color::White; }
  // Color TernaryColor() const override { return Color::Black; };

  Deck TournamentCards(Experiment experiment) const override {
    Deck deck;

    if (experiment == Experiment::exp) {
      // AddN(deck.cards, 1, MakeCard("1W", 1, "Bird"));
      AddN(deck.lands, 1, Shore());
    } else {
    }

    AddN(deck.cards, 1, MakeCard("G", 1, "MossViper"));
    AddN(deck.cards, 1, MakeCard("G", 1, "Spider"));

    AddN(deck.cards, 1, MakeCard("WG", 1, "BronzehideLion"));
    AddN(deck.cards, 1, MakeCard("1G", 1, "Beetle"));
    AddN(deck.cards, 1, MakeCard("1G", 0, "Warbriar"));
    AddN(deck.cards, 1, MakeCard("1W", 0, "IndomitableWill"));

    AddN(deck.cards, 1, MakeCard("2W", 1, "FavoredOfIroas"));
    AddN(deck.cards, 1, MakeCard("2G", 1, "NyxHerald"));
    AddN(deck.cards, 1, MakeCard("2G", 1, "Champion"));
    AddN(deck.cards, 1, MakeCard("2W", 0, "DreadfulApathy"));
    AddN(deck.cards, 1, MakeCard("2W", 0, "BanishingLight"));
    AddN(deck.cards, 1, MakeCard("3", 0, "EntrancingLyre"));

    AddN(deck.cards, 1, MakeCard("3W", 1, "Pegasus"));
    AddN(deck.cards, 1, MakeCard("2GG", 1, "Typhon"));
    AddN(deck.cards, 1, MakeCard("2GG", 1, "Typhon"));
    AddN(deck.cards, 1, MakeCard("2GG", 5, "Renata"));
    AddN(deck.cards, 1, MakeCard("3G", 0, "Mantle"));
    AddN(deck.cards, 1, MakeCard("3W", 0, "TriumphantSurge"));
    AddN(deck.cards, 1, MakeCard("2WW", 0, "Intervention"));

    AddN(deck.cards, 1, MakeCard("4G", 1, "Forerunner"));
    AddN(deck.cards, 1, MakeCard("4GG", 1, "Pheres"));
    AddN(deck.cards, 1, MakeCard("3GGG", 1, "Colossus"));
    AddN(deck.cards, 1, MakeCard("3WW", 0, "Elspeth"));

    return deck;
  }
};
