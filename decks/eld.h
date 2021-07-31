#pragma once

#include "../core/library.h"

inline Library kELD =
    Library::Builder()
        .SetLimited()
        .AddSpell(MakeSpell("R", 1, "FerventChampion"))
        .AddSpell(MakeSpell("1", 1, "ScaldingCauldron"))
        .AddSpell(MakeSpell("U", 1, "WishingWell"))

        .AddSpell(MakeSpell("1R", 1, "RimrockKnight"))
        .AddSpell(MakeSpell("1R", 2, "Robber"))
        .AddSpell(MakeSpell("1U", 2, "Faerie"))
        .AddSpell(MakeSpell("1R", 0, "Dragonfire"))
        .AddSpell(MakeSpell("1R", 0, "Dragonfire"))
        .AddSpell(MakeSpell("1R", 0, "Fling"))
        .AddSpell(MakeSpell("1U", 1, "Alliance"))

        .AddSpell(MakeSpell("2U", 1, "QueenOfIce"))
        .AddSpell(MakeSpell("2R", 1, "Trebuchet"))
        .AddSpell(MakeSpell("2R", 3, "Pyromancer"))
        .AddSpell(MakeSpell("2R", 0, "BlowYourHouseDown"))

        .AddSpell(MakeSpell("4", 1, "LochDragon"))
        .AddSpell(MakeSpell("3R", 1, "OgreErrant"))
        .AddSpell(MakeSpell("3R", 1, "SkullknockerOgre"))
        .AddSpell(MakeSpell("3R", 1, "SkullknockerOgre"))

        .AddSpell(MakeSpell("4U", 2, "SageOfTheFalls"))

        .AddSpell(MakeSpell("RRR", 1, "Clockwork"), Experiment::exp)
        .AddSpell(MakeSpell("1RRR", 1, "EmberethPaladin"), Experiment::exp)
        .AddSpell(MakeSpell("2RRR", 1, "SearingBarrage"), Experiment::exp)
        .AddSpell(MakeSpell("2UUU", 1, "UnexplainedVision"), Experiment::exp)

        .AddSpell(MakeSpell("3", 1, "Clockwork"), Experiment::base)
        .AddSpell(MakeSpell("3R", 1, "EmberethPaladin"), Experiment::base)
        .AddSpell(MakeSpell("4R", 1, "SearingBarrage"), Experiment::base)
        .AddSpell(MakeSpell("4U", 1, "UnexplainedVision"), Experiment::base)

        .Build();
