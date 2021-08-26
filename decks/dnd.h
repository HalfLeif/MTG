#pragma once

#include "../core/library.h"

inline Library kDND =
    Library::Builder()
        .SetLimited()
        .AddSpell(MakeSpell("B", 1, "Paladin").AddAbility("B2"))
        // .AddSpell(MakeSpell("1", 1, "BagOfHolding").AddAbility("2"))
        .AddSpell(MakeSpell("B", 1, "Warlock").AddAbility("B1"))
        .AddSpell(MakeSpell("BB", 1, "Sword").AddAbility("BBB5"))

        .AddSpell(MakeSpell("U1", 1, "GuildThief").AddAbility("U3"))
        .AddSpell(MakeSpell("U1", 1, "PixieGuide"))
        .AddSpell(MakeSpell("U1", 1, "PixieGuide"))

        .AddSpell(MakeSpell("U1", 0, "ShockingGrasp"))
        .AddSpell(MakeSpell("U1", 0, "FrostRay"))

        // .AddSpell(MakeSpell("U1", 1, "Arcane"), Experiment::base)
        // .AddSpell(MakeSpell("U3", 1, "Rogue"), Experiment::exp)

        .AddSpell(MakeSpell("U2", 1, "EccApprentice"))
        .AddSpell(MakeSpell("U2", 1, "SoulknifeSpy"))
        .AddSpell(MakeSpell("B2", 1, "Vampire"))
        .AddSpell(MakeSpell("B2", 1, "Vampire"))
        .AddSpell(MakeSpell("B2", 1, "YuanTiBlade"))
        .AddSpell(MakeSpell("U2", 1, "Scion"))
        .AddSpell(MakeSpell("U2", 0, "Persuasion"))
        .AddSpell(MakeSpell("UU1", 0, "Sleep"))

        .AddSpell(MakeSpell("U3", 1, "WindSeeker"))
        .AddSpell(MakeSpell("U3", 1, "ShortcutSeeker"))
        .AddSpell(MakeSpell("U3", 1, "ShortcutSeeker"))

        .AddSpell(MakeSpell("B4", 1, "Herald").AddAbility("B5").AddBonus(-1))
        .AddSpell(
            MakeSpell("5", 1, "DeckOfManyThings").AddBonus(-1).AddAbility("2"))

        .AddSpell(MakeSpell("UB4", 5, "Xanathar").AddBonus(3).AddAbility("3"))
        .AddSpell(MakeSpell("BB5", 1, "Dragon"))
        .AddLand(DualLand(Color::Blue, Color::Black))

        // .AddSpell(MakeSpell("U", 1, "Door").AddAbility("U4"),
        // Experiment::exp)
        // .AddSpell(MakeSpell("U1", 1, "Cr"), Experiment::exp2)
        // .AddSpell(MakeSpell("B2", 1, "Cr"), Experiment::exp3)

        // .AddSpell(MakeSpell("B4", 1, "Herald").AddAbility("B5").AddBonus(-1),
        //           Experiment::base)
        // .AddSpell(MakeSpell("BB3", 1, "Ogre").AddBonus(-0.5),Experiment::exp)

        .Build();
