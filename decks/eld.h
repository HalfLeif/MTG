#pragma once

#include "../core/library.h"

inline Library kELD =
    Library::Builder()
        .SetLimited()
        .AddCard(MakeCard("R", 1, "FerventChampion"))
        .AddCard(MakeCard("1", 1, "ScaldingCauldron"))
        .AddCard(MakeCard("U", 1, "WishingWell"))

        .AddCard(MakeCard("1R", 1, "RimrockKnight"))
        .AddCard(MakeCard("1R", 2, "Robber"))
        .AddCard(MakeCard("1U", 2, "Faerie"))
        .AddCard(MakeCard("1R", 0, "Dragonfire"))
        .AddCard(MakeCard("1R", 0, "Dragonfire"))
        .AddCard(MakeCard("1R", 0, "Fling"))
        .AddCard(MakeCard("1U", 1, "Alliance"))

        .AddCard(MakeCard("2U", 1, "QueenOfIce"))
        .AddCard(MakeCard("2R", 1, "Trebuchet"))
        .AddCard(MakeCard("2R", 3, "Pyromancer"))
        .AddCard(MakeCard("2R", 0, "BlowYourHouseDown"))

        .AddCard(MakeCard("4", 1, "LochDragon"))
        .AddCard(MakeCard("3R", 1, "OgreErrant"))
        .AddCard(MakeCard("3R", 1, "SkullknockerOgre"))
        .AddCard(MakeCard("3R", 1, "SkullknockerOgre"))

        .AddCard(MakeCard("4U", 2, "SageOfTheFalls"))

        .AddCard(MakeCard("RRR", 1, "Clockwork"), Experiment::exp)
        .AddCard(MakeCard("1RRR", 1, "EmberethPaladin"), Experiment::exp)
        .AddCard(MakeCard("2RRR", 1, "SearingBarrage"), Experiment::exp)
        .AddCard(MakeCard("2UUU", 1, "UnexplainedVision"), Experiment::exp)

        .AddCard(MakeCard("3", 1, "Clockwork"), Experiment::base)
        .AddCard(MakeCard("3R", 1, "EmberethPaladin"), Experiment::base)
        .AddCard(MakeCard("4R", 1, "SearingBarrage"), Experiment::base)
        .AddCard(MakeCard("4U", 1, "UnexplainedVision"), Experiment::base)

        .Build();

// class ELD : public Format {
// public:
//   static const Format &Instance() {
//     static const auto *const kInstance = new ELD;
//     return *kInstance;
//   }
//
//   Color PrimaryColor() const override { return Color::Red; }
//   Color SecondaryColor() const override { return Color::Blue; }
//
//   Deck TournamentCards(Experiment experiment) const override {
//     Deck deck;
//
//     if (experiment == Experiment::exp) { // Adamant
//
//     } else {
//     }
//
//     return deck;
//   }
// }
// ;
