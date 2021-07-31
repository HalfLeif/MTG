#pragma once

#include "../core/format.h"

class M20 : public Format {
public:
  static const Format &Instance() {
    static const auto *const kInstance = new M20;
    return *kInstance;
  }

  void ManaPreference(const Player &player, const ManaCost &mana_pool,
                      std::vector<Color> *priorities) const override {
    if (Contains<Card>(player.battlefield.cards, IsDreadPresence)) {
      // Prefer Swamps now that DreadPresence is in play!
      priorities->push_back(Color::Black);
    } else if ((Contains<Card>(player.hand.cards, IsDreadPresence) ||
                Contains<Card>(player.library.cards, IsDreadPresence)) &&
               FindWithDefault(mana_pool, Color::Black, 0) >= 2) {
      // Prefer Plains for now, to save Swamps for DreadPresence.
      priorities->push_back(Color::White);
    }
  }

  Color PrimaryColor() const override { return Color::Black; }
  Color SecondaryColor() const override { return Color::White; }

  Deck TournamentCards(Experiment experiment) const override {
    Deck deck;

    // Removed:
    // AddN(deck.cards, 1, MakeCard("1W", 1, "RaiseAlarm"));
    // AddN(deck.cards, 1, MakeCard("B", 1, "Skeleton"));
    // AddN(deck.cards, 1, MakeCard("4", 1, "Raptor"));
    // AddN(deck.cards, 1, MakeCard("2W", 1, "Sentry"));

    if (experiment == Experiment::exp) {
      AddN(deck.cards, 1, MakeCard("BB", 2, "Fenlurker"));
      AddN(deck.cards, 1, MakeCard("1W", 0, "Instant Lifelink"));
      AddN(deck.cards, 1, MakeCard("3BB", 0, "Scourger"));
    } else {
      AddN(deck.cards, 1, MakeCard("1B", 1, "Vampire"));
      AddN(deck.cards, 1, MakeCard("2W", 0, "GauntletsOfLight"));
      AddN(deck.cards, 1, MakeCard("4W", 0, "SquadCaptain"));
    }

    AddN(deck.cards, 1, MakeCard("B", 0, "BoneSplinters"));

    AddN(deck.cards, 1, MakeCard("WB", 5, "CorpseKnight"));
    AddN(deck.cards, 1, MakeCard("1W", 2, "AncientSword"));
    AddN(deck.cards, 1, MakeCard("BB", 2, "Fenlurker"));
    AddN(deck.cards, 1, MakeCard("1W", 0, "EternalIsolation"));
    AddN(deck.cards, 1, MakeCard("1W", 0, "Pacifism"));
    AddN(deck.cards, 1, MakeCard("1W", 0, "Instant Lifelink"));

    AddN(deck.cards, 1, MakeCard("2B", 2, "Thief"));
    AddN(deck.cards, 1, MakeCard("2B", 2, "Thief"));
    AddN(deck.cards, 1, MakeCard("2B", 1, "2/2 Bird"));
    AddN(deck.cards, 1, MakeCard("2W", 1, "HangedExecutioner"));
    AddN(deck.cards, 1, MakeCard("2W", 1, "1/3 Bird"));
    AddN(deck.cards, 1, MakeCard("1BB", 0, "Murder"));
    AddN(deck.cards, 1, MakeCard("1BB", 0, "EmbodimentOfAgonies"));

    AddN(deck.cards, 1, MakeCard("3B", 10, "DreadPresence"));
    AddN(deck.cards, 1, MakeCard("3W", 2, "2/3 Bird"));
    AddN(deck.cards, 1, MakeCard("3B", 0, "AgonizingSyphon"));
    AddN(deck.cards, 1, MakeCard("3B", 0, "BloodForBones"));

    AddN(deck.cards, 1, MakeCard("3BB", 1, "Necromancer"));

    AddN(deck.cards, 1, MakeCard("7", 4, "MeteorGolem"));

    return deck;
  }
};
