#pragma once

#include "../core/library.h"

inline Library kMID =
    Library::Builder()
        .SetLimited()
        .AddSpell(MakeSpell("W", 0, "Candletrap").AddOnetimeAbility("W2"))
        .AddSpell(MakeSpell("W", 0, "Candletrap").AddOnetimeAbility("W2"))
        .AddSpell(MakeSpell("W", 1, "ChaplainOfAlms").AddOnetimeAbility("W3"))
        .AddSpell(MakeSpell("W", 1, "Lunarch").AddOnetimeAbility("W1"))
        .AddSpell(MakeSpell("B", 1, "EcstaticAwakener").AddOnetimeAbility("B2"))

        .AddSpell(MakeSpell("W1", 1, "BelovedBeggar").AddOnetimeAbility("WW4"))
        .AddSpell(MakeSpell("W1", 1, "CandlegroveWitch"))
        .AddSpell(MakeSpell("W1", 1, "SungoldSentinel"))
        // .AddSpell(MakeSpell("W1", 0, "SunsetRevelry"))
        .AddSpell(MakeSpell("B1", 0, "DaggerInstant"))
        // .AddSpell(MakeSpell("B1", 1, "GhoulishProcession"), Experiment::base)
        .AddSpell(MakeSpell("B1", 0, "InfernalGrasp"))
        .AddSpell(MakeSpell("B1", 1, "SlaughterSpecialist"))
        .AddSpell(MakeSpell("B1", 1, "VengefulStrangler"))

        .AddSpell(MakeSpell("W2", 1, "MourningPatrol").AddOnetimeAbility("W3"))
        .AddSpell(MakeSpell("W2", 0, "SungoldBarrage"))
        .AddSpell(MakeSpell("WW1", 1, "Adeline"))
        .AddSpell(MakeSpell("WW1", 1, "Adeline"))
        .AddSpell(MakeSpell("WW1", 1, "GavonyDawnguard"))
        .AddSpell(MakeSpell("B2", 1, "MorbidOpportunist"))
        .AddSpell(MakeSpell("B2", 1, "ShadyTraveller"))
        .AddSpell(MakeSpell("BB1", 0, "BloodlineCulling"))

        // .AddSpell(MakeSpell("W3", 1, "ClarionCathar"))
        .AddSpell(MakeSpell("W3", 1, "GavonySilversmith"))

        .AddSpell(MakeSpell("W4", 1, "SoulguideGryff"))
        .AddSpell(MakeSpell("WW3", 1, "SigardianSavior"))

        // .AddSpell(MakeSpell("B6", 1, "BigThing"), Experiment::exp)

        // Almost identical result mana-wise, both lands and points.

        .AddLand(FetchLand())
        // .AddLand(FetchLand(), Experiment::exp)
        // .AddLand(BasicLand(Color::White), Experiment::base)

        .Build();
