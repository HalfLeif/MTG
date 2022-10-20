#pragma once

#include "../core/library.h"

inline Library kDMU =
    Library::Builder()
        .SetLimited()
        .AddSpell(MakeSpell("G6", 1, "Herd").AddOnetimeAbility("G1"))
        .AddSpell(MakeSpell("W4", 1, "Angel").AddOnetimeAbility("G1"))
        .AddSpell(MakeSpell("GGG2", 1, "Shaman"))
        .AddSpell(MakeSpell("GG3", 1, "Baloth"))
        .AddSpell(MakeSpell("GG3", 1, "Baloth"))
        .AddSpell(MakeSpell("G3", 1, "Sojourner"))
        .AddSpell(MakeSpell("W2", 1, "FlashBird").AddOnetimeAbility("R2"))
        .AddSpell(MakeSpell("3", 1, "Librarian"))
        .AddSpell(MakeSpell("G2", 1, "Gardener"))
        .AddSpell(MakeSpell("G2", 1, "Greenwidow").AddOnetimeAbility("G3"))
        .AddSpell(MakeSpell("W", 1, "Drawbridge").AddAbility("W2"))
        .AddSpell(MakeSpell("G1", 1, "Brawler"))
        .AddSpell(MakeSpell("G1", 1, "Lizard").AddAbility("G3"))
        .AddSpell(MakeSpell("G1", 1, "Lizard").AddAbility("G3"))
        .AddSpell(MakeSpell("W1", 1, "Knight").AddAbility("W1"))
        .AddSpell(MakeSpell("G2", 1, "ScoutWilderness").AddOnetimeAbility("W1"))
        .AddSpell(MakeSpell("G1", 0, "BiteDown"))
        .AddSpell(MakeSpell("W1", 0, "DestroyEvil"))
        .AddSpell(MakeSpell("G", 0, "TailSwipe"))
        .AddSpell(MakeSpell("G", 0, "TailSwipe"))
        .AddSpell(MakeSpell("G1", 0, "ColossalGrowth").AddOnetimeAbility("R"))
        .AddSpell(MakeSpell("G", 0, "Might"))
        .AddSpell(MakeSpell("G", 0, "Might"))

        .AddLand(DualLand("GU"))
        .AddLand(DualLand("BG"))
        .AddLand(DualLand("RG"))
        .AddLand(DualLand("RG"))
        .AddLand(DualLand("WU"))
        .AddLand(DualLand("WB"))
        .AddLand(DualLand("RW"))

        .Build();
