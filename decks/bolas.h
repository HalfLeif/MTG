#pragma once

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

        .AddSpell(MakeSpell("1", 10, "SolRing"))
        .AddSpell(MakeSpell("B", 0, "DeadlyStuff"))
        // .AddSpell(MakeSpell("U", 0, "Annul"), Experiment::base)

        .AddSpell(MakeSpell("B", 1, "EbenholzKnight"))
        .AddSpell(MakeSpell("B", 1, "Gutterbones"))
        .AddSpell(MakeSpell("B", 1, "Gutterbones"))
        // .AddSpell(MakeSpell("B", 1, "FoulmireKnight"), Experiment::exp)
        // .AddSpell(MakeSpell("1B", 1, "Swordmaster"))
        // .AddSpell(MakeSpell("2B", 1, "Pestil"), Experiment::exp)

        //
        // .AddSpell(MakeSpell("1B", 1, "BlacklanceParagon"), Experiment::base)
        // .AddSpell(MakeSpell("BB", 1, "Fenlurker"))
        // .AddSpell(MakeSpell("BB", 1, "Fenlurker"))
        .AddSpell(MakeSpell("1R", 1, "Reveler"))
        .AddSpell(MakeSpell("1R", 1, "WallOfRazors"))
        .AddSpell(MakeSpell("1U", 1, "Flyer"))
        .AddSpell(MakeSpell("1U", 1, "FaerieDuelist"))
        //
        .AddSpell(MakeSpell("1B", 0, "AidFallen"))
        .AddSpell(MakeSpell("1B", 0, "AidFallen"))
        .AddSpell(MakeSpell("UB", 0, "TyrantScorn"))
        .AddSpell(MakeSpell("UB", 0, "TyrantScorn"))
        .AddSpell(MakeSpell("1R", 0, "MagmaJet"))
        .AddSpell(MakeSpell("1R", 0, "MagmaJet"))
        .AddSpell(MakeSpell("1R", 0, "MagmaJet"))
        // .AddSpell(MakeSpell("1R", 0, "Pyroclasm"))
        // .AddSpell(MakeSpell("1R", 0, "MagmaJet"), Experiment::exp)

        .AddSpell(MakeSpell("2B", 1, "PestilentSpirit"))
        .AddSpell(MakeSpell("2B", 3, "Sensenmann"))
        .AddSpell(MakeSpell("1BB", 0, "EmbodimentOfAgonies"))
        .AddSpell(MakeSpell("2R", 1, "Alesha"))
        // .AddSpell(MakeSpell("2U", 1, "Drake"), Experiment::base)
        .AddSpell(MakeSpell("2B", 1, "Bird"))
        // .AddSpell(MakeSpell("2U", 1, "Pioneer"))
        .AddSpell(MakeSpell("2R", 1, "Trebuchet"))

        // .AddSpell(MakeSpell("2B", 0, "ObNixilisCruelty"))
        // .AddSpell(MakeSpell("2B", 0, "ObNixilisCruelty"))
        // .AddSpell(MakeSpell("1BB", 0, "BleedingEdge"))
        .AddSpell(MakeSpell("1BB", 0, "WitchVengeance"))
        .AddSpell(MakeSpell("1BB", 0, "WitchVengeance"))
        // .AddSpell(MakeSpell("1BB", 0, "RuinousPath"))
        // .AddSpell(MakeSpell("1BB", 0, "RuinousPath"))

        .AddSpell(MakeSpell("3B", 5, "DreadPresence"))
        .AddSpell(MakeSpell("3B", 1, "Spawn"))
        .AddSpell(MakeSpell("2UB", 0, "HostageTaker"))

        .AddSpell(MakeSpell("3U", 0, "SparkDouble"))
        .AddSpell(MakeSpell("2UR", 0, "RalsOutburst"))
        .AddSpell(MakeSpell("3B", 1, "RevengeRavens"))

        //
        .AddSpell(MakeSpell("3BB", 1, "MassacreGirl"))
        .AddSpell(MakeSpell("UBBBR", 4, "NicolBolas"))
        .AddSpell(MakeSpell("UBBBR", 4, "NicolBolas"))
        .AddSpell(MakeSpell("2UBR", 0, "DarkIntimations"))
        //
        // .AddSpell(MakeSpell("3BBB", 1, "KayaBane"))
        .AddSpell(MakeSpell("4UB", 4, "DriftingDeath"))
        .AddSpell(MakeSpell("6", 10, "UginIneffable"))
        // .AddSpell(MakeSpell("4", 0, "StonecoilSerpent"))
        //
        // .AddSpell(MakeSpell("5BR", 1, "CaptiveAudience"))
        // .AddSpell(MakeSpell("5BR", 1, "CaptiveAudience"))
        //
        // .AddSpell(MakeSpell("8", 1, "ElderDeepfiend"), Experiment::base)
        // .AddSpell(MakeSpell("5UU", 1, "ElderDeepfiend"), Experiment::base)

        // .AddSpell(MakeSpell("BBRR", 1, "FireWheeler"), Experiment::exp)
        .Build();
