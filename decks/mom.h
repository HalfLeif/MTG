#pragma once

#include <string_view>
#include <vector>

#include "../core/sealed_deck.h"

// March of the Machine (2023)
class Mom : public SealedDeck {
public:
  std::string_view data_path() const override { return "data/mom/cards.csv"; }

  std::vector<std::string_view> chosen_deck() const override {
    return {
        "SurgeofSalvation",
        "AngelicIntervention",
        "TarkirDuneshaper",
        "AetherbladeAgent",
        "NornsInquisitor",
        "MonasteryMentor",
        "RealmbreakersGrasp",
        "ElvishVatkeeper",
        "CompleatedHuntmaster",
        "InvasionofBelenon",
        "PhyrexianAwakening",
        "KithkinBillyrider",
        "CutShort",
        //
        "DranaandLinvala",
        "SculptedPerfection",
        "DeadlyDerision",
        "DeadlyDerision",
        "InfectedDefector",
        "InfectedDefector",
        "EtchedHostDoombringer",
        "FailedConversion",
        "InvasionofLorwyn",
        "GloomfangMauler",
    };
  };
};

/**

65.3 (88.2 - 22.8) Lands { B=6 G=5 W=5 WG=1 }
66.1 (88.3 - 22.2) Lands { B=5 G=4 W=7 WG=1 }
66.5 (88.2 - 21.7) Lands { B=5 G=2 W=9 WG=1 }
67.0 (88.1 - 21.0) Lands { B=5 G=1 W=10 WG=1 }
67.9 (89.8 - 21.8) Lands { B=6 G=4 W=6 WG=1 }
68.5 (88.4 - 19.9) Lands { B=6 W=10 WG=1 }
69.1 (90.1 - 21.0) Lands { B=5 G=3 W=8 WG=1 }
69.4 (90.8 - 21.4) Lands { B=6 G=3 W=7 WG=1 }
70.2 (90.5 - 20.4) Lands { B=6 G=1 W=9 WG=1 }
72.7 (92.3 - 19.6) Lands { B=6 G=2 W=8 WG=1 }

    3590 GloomfangMauler (BB5)
    5058 TarkirDuneshaper (W)
    5233 SurgeofSalvation (W)
    5457 KithkinBillyrider (W2)
    5789 AngelicIntervention (W1)
    6307 InfectedDefector (W4)
    6307 InfectedDefector (W4)
    6320 CutShort (W2)
    7141 AetherbladeAgent (B1)
    7148 EtchedHostDoombringer (B4)
    8140 InvasionofLorwyn (BG4)
    8355 DeadlyDerision (BB2)
    8355 DeadlyDerision (BB2)
    8681 ElvishVatkeeper (BG1)
    8913 RealmbreakersGrasp (W1)
    8956 CompleatedHuntmaster (B2)
    9195 FailedConversion (B4)
   10978 NornsInquisitor (W1)
   11000 MonasteryMentor (W2)
   11530 SculptedPerfection (WB2)
   12425 PhyrexianAwakening (W2)
   12454 InvasionofBelenon (W2)
   14923 DranaandLinvala (WWB1)

*/
