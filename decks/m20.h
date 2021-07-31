#pragma once

#include "../core/library.h"

inline Library kM20 =
    Library::Builder()
        .SetLimited()
        .AddCard(MakeCard("B", 0, "BoneSplinters"))

        .AddCard(MakeCard("WB", 5, "CorpseKnight"))
        .AddCard(MakeCard("1W", 2, "AncientSword"))
        .AddCard(MakeCard("BB", 2, "Fenlurker"))
        .AddCard(MakeCard("1W", 0, "EternalIsolation"))
        .AddCard(MakeCard("1W", 0, "Pacifism"))
        .AddCard(MakeCard("1W", 0, "Instant Lifelink"))

        .AddCard(MakeCard("2B", 2, "Thief"))
        .AddCard(MakeCard("2B", 2, "Thief"))
        .AddCard(MakeCard("2B", 1, "2/2 Bird"))
        .AddCard(MakeCard("2W", 1, "HangedExecutioner"))
        .AddCard(MakeCard("2W", 1, "1/3 Bird"))
        .AddCard(MakeCard("1BB", 0, "Murder"))
        .AddCard(MakeCard("1BB", 0, "EmbodimentOfAgonies"))

        .AddCard(MakeCard("3B", 10, "DreadPresence"))
        .AddCard(MakeCard("3W", 2, "2/3 Bird"))
        .AddCard(MakeCard("3B", 0, "AgonizingSyphon"))
        .AddCard(MakeCard("3B", 0, "BloodForBones"))

        .AddCard(MakeCard("3BB", 1, "Necromancer"))

        .AddCard(MakeCard("7", 4, "MeteorGolem"))

        .AddCard(MakeCard("BB", 2, "Fenlurker"), Experiment::exp)
        .AddCard(MakeCard("1W", 0, "Instant Lifelink"), Experiment::exp)
        .AddCard(MakeCard("3BB", 0, "Scourger"), Experiment::exp)

        .AddCard(MakeCard("1B", 1, "Vampire"), Experiment::base)
        .AddCard(MakeCard("2W", 0, "GauntletsOfLight"), Experiment::base)
        .AddCard(MakeCard("4W", 0, "SquadCaptain"), Experiment::base)

        .Build();
