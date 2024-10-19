#pragma once

#include "../core/library.h"

inline Library kBMB =
    Library::Builder()
        .SetLimited()
        .AddSpell(MakeSpell("W1", 1, "PumpRabbit").AddAbility("W3"))
        .AddSpell(MakeSpell("W1", 1, "MrHamster"))
        .AddSpell(MakeSpell("W1", 1, "BatBird"))
        .AddSpell(MakeSpell("B1", 1, "DeathSquirrel"))
        .AddSpell(MakeSpell("W1", 0, "AwesomeClericBatGrower").AddBonus(1))

        .AddSpell(MakeSpell("3", 1, "LifeBat"))
        .AddSpell(MakeSpell("3", 1, "LifeBat"))
        .AddSpell(MakeSpell("WB1", 1, "Zoraline").AddOnetimeAbility("WB").AddBonus(1))
        .AddSpell(MakeSpell("W2", 1, "Rabbit3/3"))
        .AddSpell(MakeSpell("W2", 1, "HopToIt"))

        // DeathSquirrel is more useful to keep than DeathRat.
        // .AddSpell(MakeSpell("B2", 1, "DeathRat"), Experiment::exp)

        .AddSpell(MakeSpell("W3", 1, "IntrepidRabbit+1"))
        .AddSpell(MakeSpell("W3", 1, "IntrepidRabbit+1"))
        .AddSpell(MakeSpell("BB2", 1, "DarkAugur+1").AddBonus(1))
        .AddSpell(MakeSpell("W3", 1, "StarCharterBat"))
        .AddSpell(MakeSpell("W3", 1, "VigilanceBat"))

        // Keeping Hamster, and DeathRat -> ShortBow seems useful
        .AddSpell(MakeSpell("2", 0, "ShortBow").AddOnetimeAbility("1"))
        .AddSpell(MakeSpell("3", 2, "PatchworkBanner").AddBonus(-0.5))
        .AddSpell(MakeSpell("B3", 1, "LifestealArtifact"))

        .AddSpell(MakeSpell("W", 0, "CombatTrick+2/2"))
        .AddSpell(MakeSpell("W1", 0, "BatSonar"))
        .AddSpell(MakeSpell("W1", 0, "BatSonar"))
        .AddSpell(MakeSpell("B2", 0, "DestroyCreature"))
        .AddSpell(MakeSpell("WW2", 0, "RabbitResponse"))

        // Apparently not worth going to 16 lands...
        // Even with mana from PatchworkBanner


        .AddLand(Shore())

        .Build();

/* exp=ShortBow
39.6 (50.2 - 10.6) exp Lands { B=9 W=7 Shore=1 }
40.1 (50.4 - 10.4) exp Lands { B=8 W=8 Shore=1 }
40.1 (50.0 - 9.8) exp Lands { B=5 W=11 Shore=1 }
40.5 (50.4 - 9.9) base Lands { B=4 W=12 Shore=1 }
40.7 (50.6 - 9.9) exp Lands { B=6 W=10 Shore=1 }
40.8 (50.7 - 9.9) exp Lands { B=7 W=9 Shore=1 }
41.2 (51.3 - 10.1) base Lands { B=8 W=8 Shore=1 }
41.2 (51.0 - 9.8) base Lands { B=5 W=11 Shore=1 }
41.6 (51.3 - 9.8) base Lands { B=6 W=10 Shore=1 }
41.7 (51.6 - 9.9) base Lands { B=7 W=9 Shore=1 }

    5026 BatSonar (W1)
    5026 BatSonar (W1)
    5268 CombatTrick+2/2 (W)
    8501 DestroyCreature (B2)
   10089 RabbitResponse (WW2)
   10396 DeathSquirrel (B1)
   11132 BatBird (W1)
   11136 AwesomeClericBatGrower (W1)
   11174 LifeBat (3)
   11174 LifeBat (3)
   11294 PatchworkBanner (3)
   11310 DeathRat (B2)
   11385 Rabbit3/3 (W2)
   11440 HopToIt (W2)
   11726 MrHamster (W1)
   11795 PumpRabbit (W1)
   13626 LifestealArtifact (B3)
   13683 IntrepidRabbit+1 (W3)
   13683 IntrepidRabbit+1 (W3)
   13688 StarCharterBat (W3)
   14183 VigilanceBat (W3)
   16082 DarkAugur+1 (BB2)
   19783 Zoraline (WB1)

*/
