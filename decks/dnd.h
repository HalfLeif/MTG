#pragma once

#include "../core/library.h"

inline Library kDND =
    Library::Builder()
        .SetLimited()
        .AddSpell(MakeSpell("B", 1, "Paladin").AddAbility("B2"))
        .AddSpell(MakeSpell("1", 1, "BagOfHolding").AddAbility("2"))
        .AddSpell(MakeSpell("BB", 1, "Sword").AddAbility("BBB5"))

        .AddSpell(MakeSpell("U1", 1, "GuildThief").AddAbility("U3"))
        .AddSpell(MakeSpell("U1", 1, "PixieGuide"))
        .AddSpell(MakeSpell("U1", 1, "PixieGuide"))
        .AddSpell(MakeSpell("U1", 0, "ShockingGrasp"))
        .AddSpell(MakeSpell("B1", 0, "GrimWanderer"))

        .AddSpell(MakeSpell("U2", 1, "EccApprentice"))
        .AddSpell(MakeSpell("U2", 1, "SoulknifeSpy"))
        .AddSpell(MakeSpell("B2", 1, "Vampire"))
        .AddSpell(MakeSpell("B2", 1, "YuanTiBlade"))
        .AddSpell(MakeSpell("U2", 0, "BarTheGate"))
        .AddSpell(MakeSpell("U2", 0, "Persuasion"))
        .AddSpell(MakeSpell("UU1", 0, "Sleep"))

        .AddSpell(MakeSpell("U3", 1, "WindSeeker"))
        .AddSpell(MakeSpell("U3", 1, "ShortcutSeeker"))

        .AddSpell(MakeSpell("B4", 1, "Herald").AddAbility("B5").AddBonus(-1))
        .AddSpell(MakeSpell("B4", 1, "Herald").AddAbility("B5").AddBonus(-1),
                  Experiment::base)
        .AddSpell(MakeSpell("BB3", 1, "Ogre").AddBonus(-0.5), Experiment::base)

        .AddSpell(MakeSpell("5", 1, "DeckOfManyThings").AddAbility("2"))

        .AddSpell(MakeSpell("UB4", 1, "Xanathar"))
        .AddSpell(MakeSpell("BB5", 1, "Dragon"))
        .AddLand(DualLand(Color::Blue, Color::Black))

        .AddSpell(MakeSpell("U1", 0, "FrostRay"), Experiment::exp)
        .AddSpell(MakeSpell("B4", 1, "Herald").AddAbility("B5").AddBonus(-1),
                  Experiment::exp)

        .AddSpell(MakeSpell("U1", 0, "FrostRay"), Experiment::exp2)
        .AddSpell(MakeSpell("BB3", 1, "Ogre").AddBonus(-0.5), Experiment::exp2)

        // .AddSpell(MakeSpell("B2", 1, "Vampire"), Experiment::exp)
        // .AddSpell(MakeSpell("U", 1, "Door").AddAbility("U4"),
        // Experiment::exp)

        .Build();
