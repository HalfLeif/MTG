#pragma once

#include "../core/library.h"

inline Library kBMB =
    Library::Builder()
        .SetLimited()
        .AddSpell(MakeSpell("W1", 1, "PumpRabbit").AddAbility("W3"))
        .AddSpell(MakeSpell("W1", 1, "MrHamster"), Experiment::base)
        .AddSpell(MakeSpell("W1", 1, "BatBird"))
        .AddSpell(MakeSpell("B1", 1, "DeathSquirrel"))
        .AddSpell(MakeSpell("W1", 0, "AwesomeClericBatGrower").AddBonus(1))

        .AddSpell(MakeSpell("3", 1, "LifeBat"))
        .AddSpell(MakeSpell("3", 1, "LifeBat"))
        .AddSpell(MakeSpell("WB1", 1, "Zoraline").AddOnetimeAbility("WB").AddBonus(1))
        .AddSpell(MakeSpell("W2", 1, "Rabbit3/3"))
        .AddSpell(MakeSpell("W2", 1, "HopToIt"))

        .AddSpell(MakeSpell("W3", 1, "IntrepidRabbit+1"))
        .AddSpell(MakeSpell("W3", 1, "IntrepidRabbit+1"))
        .AddSpell(MakeSpell("BB2", 1, "DarkAugur+1").AddBonus(1))
        .AddSpell(MakeSpell("W3", 1, "StarCharterBat"))
        .AddSpell(MakeSpell("W3", 1, "VigilanceBat"))

        .AddSpell(MakeSpell("3", 1, "PatchworkBanner"))
        .AddSpell(MakeSpell("B3", 1, "LifestealArtifact"))

        .AddSpell(MakeSpell("W", 0, "CombatTrick+2/2"))
        .AddSpell(MakeSpell("W1", 0, "BatSonar"))
        .AddSpell(MakeSpell("W1", 0, "BatSonar"))
        .AddSpell(MakeSpell("W1", 0, "BatSonar"))
        .AddSpell(MakeSpell("B2", 0, "DestroyCreature"))
        .AddSpell(MakeSpell("WW2", 0, "RabbitResponse"))

        // Apparently not worth going to 16 lands...
        // Unless I can simulate Mana ability of PatchworkBanner?
        .AddSpell(MakeSpell("2", 0, "ShortBow").AddOnetimeAbility("1"), Experiment::exp)

        .AddLand(Shore())

        .Build();

/* exp=ShortBow 16 lands
39.5 (50.0 - 10.5) exp Lands { B=4 W=11 Shore=1 }
39.5 (49.5 - 9.9) Lands { B=3 W=13 Shore=1 }
39.6 (50.5 - 10.9) exp Lands { B=7 W=8 Shore=1 }
40.4 (50.8 - 10.4) exp Lands { B=5 W=10 Shore=1 }
40.5 (50.9 - 10.4) Lands { B=8 W=8 Shore=1 }
40.5 (50.3 - 9.8) Lands { B=4 W=12 Shore=1 }
40.7 (51.0 - 10.3) exp Lands { B=6 W=9 Shore=1 }
41.2 (51.3 - 10.1) Lands { B=7 W=9 Shore=1 }
41.2 (51.0 - 9.8) Lands { B=5 W=11 Shore=1 }
41.3 (51.1 - 9.9) Lands { B=6 W=10 Shore=1 }

    5263 CombatTrick+2/2 (W)
    5588 BatSonar (W1)
    5588 BatSonar (W1)
    5588 BatSonar (W1)
    8614 DestroyCreature (B2)
   10393 RabbitResponse (WW2)
   10759 DeathSquirrel (B1)
   10929 BatBird (W1)
   10934 AwesomeClericBatGrower (W1)
   11821 MrHamster (W1)
   12160 PumpRabbit (W1)
   12162 LifeBat (3)
   12162 LifeBat (3)
   12169 PatchworkBanner (3)
   12569 HopToIt (W2)
   12587 Rabbit3/3 (W2)
   13189 LifestealArtifact (B3)
   13228 VigilanceBat (W3)
   13612 StarCharterBat (W3)
   13657 IntrepidRabbit+1 (W3)
   13657 IntrepidRabbit+1 (W3)
   14524 DarkAugur+1 (BB2)
   19693 Zoraline (WB1)
*/
