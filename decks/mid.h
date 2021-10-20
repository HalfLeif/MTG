#pragma once

#include "../core/library.h"

inline Library kMID =
    Library::Builder()
        .SetLimited()
        .AddSpell(MakeSpell("W", 0, "Candletrap").AddOnetimeAbility("W2"))
        .AddSpell(MakeSpell("W", 1, "ChaplainOfAlms").AddOnetimeAbility("W3"))
        .AddSpell(MakeSpell("W", 1, "ChaplainOfAlms").AddOnetimeAbility("W3"))
        .AddSpell(MakeSpell("B", 1, "EcstaticAwakener").AddOnetimeAbility("B2"))
        .AddSpell(MakeSpell("R2", 0, "LunarFrenzy"))

        .AddSpell(MakeSpell("W1", 1, "CandlegroveWitch"))
        .AddSpell(MakeSpell("W1", 1, "SungoldSentinel"))
        .AddSpell(MakeSpell("B1", 1, "GhoulishProcession"))
        .AddSpell(MakeSpell("B1", 1, "SlaughterSpecialist"))
        .AddSpell(MakeSpell("B1", 1, "VengefulStrangler"))
        .AddSpell(MakeSpell("R1", 0, "CatharticPyre"))
        .AddSpell(MakeSpell("B1", 0, "InfernalGrasp"))

        .AddSpell(MakeSpell("W2", 1, "MourningPatrol").AddOnetimeAbility("W3"))
        .AddSpell(MakeSpell("W2", 0, "SungoldBarrage"))
        .AddSpell(MakeSpell("WW1", 1, "Adeline"))
        .AddSpell(MakeSpell("WW1", 1, "GavonyDawnguard"))
        .AddSpell(MakeSpell("B2", 1, "MorbidOpportunist"))
        .AddSpell(MakeSpell("BB1", 0, "BloodlineCulling").AddBonus(1))
        .AddSpell(MakeSpell("R2", 0, "MoonragerSlash"))
        .AddSpell(MakeSpell("BR1", 1, "Florian").AddBonus(1))

        .AddSpell(MakeSpell("W3", 1, "ClarionCathar"))
        .AddSpell(MakeSpell("W3", 1, "GavonySilversmith"))

        .AddSpell(MakeSpell("WW3", 1, "SigardianSavior"))

        // .AddSpell(MakeSpell("B4", 1, "BigThing"), Experiment::exp)

        .AddLand(FetchLand())
        .AddLand(FetchLand())
        // .AddLand(FetchLand(), Experiment::exp)
        // .AddLand(BasicLand(Color::White), Experiment::base)

        .Build();
