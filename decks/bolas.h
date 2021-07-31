#pragma once

#include "../core/data.h"
#include "../core/library.h"

inline Library kBolas =
    Library::Builder()
        .SetConstructed()
        .AddLand(DualLand(Color::Black, Color::Red))
        .AddLand(DualLand(Color::Black, Color::Red))
        .AddLand(DualLand(Color::Black, Color::Red))
        .AddLand(DualLand(Color::Black, Color::Red))
        // .AddLand(DualLand(Color::Black, Color::Red))
        .AddLand(DualLand(Color::Black, Color::Red), Experiment::exp)
        // .AddLand(FetchLand(), Experiment::exp)

        .AddLand(DualLand(Color::Blue, Color::Red))
        .AddLand(DualLand(Color::Blue, Color::Red))
        .AddLand(DualLand(Color::Blue, Color::Red))
        .AddLand(DualLand(Color::Blue, Color::Red))

        .AddLand(DualLand(Color::Black, Color::Blue))
        .AddLand(DualLand(Color::Black, Color::Blue))
        // .AddLand(FetchLand(), Experiment::exp)
        // .AddLand(DualLand(Color::Blue, Color::Red), Experiment::base)
        // .AddLand(DualLand(Color::Black, Color::Blue), Experiment::exp)
        // .AddLand(DualLand(Color::Blue, Color::Red), Experiment::exp)

        .AddCard(MakeCard("1", 10, "SolRing"))
        .AddCard(MakeCard("B", 0, "DeadlyStuff"))
        // .AddCard(MakeCard("U", 0, "Annul"), Experiment::base)

        .AddCard(MakeCard("B", 1, "EbenholzKnight"))
        .AddCard(MakeCard("B", 1, "Gutterbones"))
        .AddCard(MakeCard("B", 1, "Gutterbones"))
        // .AddCard(MakeCard("B", 1, "FoulmireKnight"), Experiment::exp)
        // .AddCard(MakeCard("1B", 1, "Swordmaster"))
        // .AddCard(MakeCard("2B", 1, "Pestil"), Experiment::exp)

        //
        // .AddCard(MakeCard("1B", 1, "BlacklanceParagon"), Experiment::base)
        // .AddCard(MakeCard("BB", 1, "Fenlurker"))
        // .AddCard(MakeCard("BB", 1, "Fenlurker"))
        .AddCard(MakeCard("1R", 1, "Reveler"))
        .AddCard(MakeCard("1R", 1, "WallOfRazors"))
        .AddCard(MakeCard("1U", 1, "Flyer"))
        .AddCard(MakeCard("1U", 1, "FaerieDuelist"))
        //
        .AddCard(MakeCard("1B", 0, "AidFallen"))
        .AddCard(MakeCard("1B", 0, "AidFallen"))
        .AddCard(MakeCard("UB", 0, "TyrantScorn"))
        .AddCard(MakeCard("UB", 0, "TyrantScorn"))
        .AddCard(MakeCard("1R", 0, "MagmaJet"))
        .AddCard(MakeCard("1R", 0, "MagmaJet"))
        .AddCard(MakeCard("1R", 0, "MagmaJet"))
        // .AddCard(MakeCard("1R", 0, "Pyroclasm"))
        // .AddCard(MakeCard("1R", 0, "MagmaJet"), Experiment::exp)

        .AddCard(MakeCard("2B", 1, "PestilentSpirit"))
        .AddCard(MakeCard("2B", 3, "Sensenmann"))
        .AddCard(MakeCard("1BB", 0, "EmbodimentOfAgonies"))
        .AddCard(MakeCard("2R", 1, "Alesha"))
        // .AddCard(MakeCard("2U", 1, "Drake"), Experiment::base)
        .AddCard(MakeCard("2B", 1, "Bird"))
        // .AddCard(MakeCard("2U", 1, "Pioneer"))
        .AddCard(MakeCard("2R", 1, "Trebuchet"))

        // .AddCard(MakeCard("2B", 0, "ObNixilisCruelty"))
        // .AddCard(MakeCard("2B", 0, "ObNixilisCruelty"))
        // .AddCard(MakeCard("1BB", 0, "BleedingEdge"))
        .AddCard(MakeCard("1BB", 0, "WitchVengeance"))
        .AddCard(MakeCard("1BB", 0, "WitchVengeance"))
        // .AddCard(MakeCard("1BB", 0, "RuinousPath"))
        // .AddCard(MakeCard("1BB", 0, "RuinousPath"))

        .AddCard(MakeCard("3B", 5, "DreadPresence"))
        .AddCard(MakeCard("3B", 1, "Spawn"))
        .AddCard(MakeCard("2UB", 0, "HostageTaker"))

        .AddCard(MakeCard("3U", 0, "SparkDouble"))
        .AddCard(MakeCard("2UR", 0, "RalsOutburst"))
        .AddCard(MakeCard("3B", 1, "RevengeRavens"))

        //
        .AddCard(MakeCard("3BB", 1, "MassacreGirl"))
        .AddCard(MakeCard("UBBBR", 4, "NicolBolas"))
        .AddCard(MakeCard("UBBBR", 4, "NicolBolas"))
        .AddCard(MakeCard("2UBR", 0, "DarkIntimations"))
        //
        // .AddCard(MakeCard("3BBB", 1, "KayaBane"))
        .AddCard(MakeCard("4UB", 4, "DriftingDeath"))
        .AddCard(MakeCard("6", 10, "UginIneffable"))
        // .AddCard(MakeCard("4", 0, "StonecoilSerpent"))
        //
        // .AddCard(MakeCard("5BR", 1, "CaptiveAudience"))
        // .AddCard(MakeCard("5BR", 1, "CaptiveAudience"))
        //
        // .AddCard(MakeCard("8", 1, "ElderDeepfiend"), Experiment::base)
        // .AddCard(MakeCard("5UU", 1, "ElderDeepfiend"), Experiment::base)

        // .AddCard(MakeCard("BBRR", 1, "FireWheeler"), Experiment::exp)
        .Build();

// TODO add tap lands...
