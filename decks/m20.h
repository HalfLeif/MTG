#pragma once

#include "../core/library.h"

inline Library kM20 =
    Library::Builder()
        .SetLimited()
        .AddSpell(MakeSpell("B", 0, "BoneSplinters"))

        .AddSpell(MakeSpell("WB", 5, "CorpseKnight"))
        .AddSpell(MakeSpell("1W", 2, "AncientSword"))
        .AddSpell(MakeSpell("BB", 2, "Fenlurker").AddBonus(1))
        .AddSpell(MakeSpell("1W", 0, "EternalIsolation"))
        .AddSpell(MakeSpell("1W", 0, "Pacifism"))
        .AddSpell(MakeSpell("1W", 0, "Instant Lifelink"))

        .AddSpell(MakeSpell("2B", 2, "Thief"))
        .AddSpell(MakeSpell("2B", 2, "Thief"))
        .AddSpell(MakeSpell("2B", 1, "2/2 Bird"))
        .AddSpell(MakeSpell("2W", 1, "HangedExecutioner"))
        .AddSpell(MakeSpell("2W", 1, "1/3 Bird"))
        .AddSpell(MakeSpell("1BB", 0, "Murder"))
        .AddSpell(MakeSpell("1BB", 0, "EmbodimentOfAgonies"))

        .AddSpell(MakeSpell("3B", 10, "DreadPresence"))
        .AddSpell(MakeSpell("3W", 2, "2/3 Bird"))
        .AddSpell(MakeSpell("3B", 0, "AgonizingSyphon"))
        .AddSpell(MakeSpell("3B", 0, "BloodForBones"))

        .AddSpell(MakeSpell("3BB", 1, "Necromancer"))

        .AddSpell(MakeSpell("7", 4, "MeteorGolem"))

        .AddSpell(MakeSpell("BB", 2, "Fenlurker"), Experiment::exp)
        .AddSpell(MakeSpell("1W", 0, "Instant Lifelink"), Experiment::exp)
        .AddSpell(MakeSpell("3BB", 0, "Scourger"), Experiment::exp)

        .AddSpell(MakeSpell("1B", 1, "Vampire"), Experiment::base)
        .AddSpell(MakeSpell("2W", 0, "GauntletsOfLight"), Experiment::base)
        .AddSpell(MakeSpell("4W", 0, "SquadCaptain"), Experiment::base)

        .Build();
