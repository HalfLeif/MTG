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
        //
        "GloomfangMauler",
    };
  };
};

/**

70.1 (91.0 - 20.8) Lands { B=9 G=1 W=6 WG=1 }
70.7 (90.1 - 19.4) Lands { B=7 W=9 WG=1 }
71.2 (90.3 - 19.1) Lands { B=8 W=8 WG=1 }
71.3 (90.8 - 19.5) Lands { B=6 G=1 W=9 WG=1 }
71.4 (92.3 - 20.9) Lands { B=7 G=3 W=6 WG=1 }
71.6 (92.3 - 20.7) Lands { B=8 G=2 W=6 WG=1 }
72.2 (92.1 - 19.9) Lands { B=7 G=2 W=7 WG=1 }
72.5 (91.9 - 19.3) Lands { B=6 G=2 W=8 WG=1 }
72.8 (91.8 - 19.0) Lands { B=7 G=1 W=8 WG=1 }
72.9 (92.2 - 19.3) Lands { B=8 G=1 W=7 WG=1 }

    4330 GloomfangMauler (BB5)
    4483 TarkirDuneshaper (W)
    5025 KithkinBillyrider (W2)
    5308 InvasionofLorwyn (BG4)
    5422 SurgeofSalvation (W)
    5667 AngelicIntervention (W1)
    5970 ElvishVatkeeper (BG1)
    6113 CutShort (W2)
    6264 InfectedDefector (W4)
    6264 InfectedDefector (W4)
    7480 EtchedHostDoombringer (B4)
    7683 AetherbladeAgent (B1)
    9164 RealmbreakersGrasp (W1)
    9318 CompleatedHuntmaster (B2)
    9570 FailedConversion (B4)
   10088 NornsInquisitor (W1)
   10914 MonasteryMentor (W2)
   11070 DeadlyDerision (BB2)
   11070 DeadlyDerision (BB2)
   11535 SculptedPerfection (WB2)
   11965 PhyrexianAwakening (W2)
   12348 InvasionofBelenon (W2)
   14779 DranaandLinvala (WWB1)

71.1 (90.1 - 19.0) base Lands { B=8 W=8 WG=1 }
71.3 (92.3 - 21.0) base Lands { B=7 G=3 W=6 WG=1 }
71.7 (91.1 - 19.5) base Lands { B=6 G=1 W=9 WG=1 }
71.8 (92.5 - 20.7) base Lands { B=8 G=2 W=6 WG=1 }
71.9 (90.6 - 18.8) exp Lands { B=7 W=8 UG=1 WG=1 }
72.2 (92.1 - 19.9) base Lands { B=7 G=2 W=7 WG=1 }
72.4 (91.4 - 19.1) exp Lands { B=8 W=7 UG=1 WG=1 }
72.4 (91.9 - 19.5) base Lands { B=6 G=2 W=8 WG=1 }
72.7 (91.8 - 19.1) base Lands { B=7 G=1 W=8 WG=1 }
73.2 (92.4 - 19.2) base Lands { B=8 G=1 W=7 WG=1 }

    4402 GloomfangMauler (BB5)
    4487 TarkirDuneshaper (W)
    5014 KithkinBillyrider (W2)
    5409 SurgeofSalvation (W)
    5671 AngelicIntervention (W1)
    5752 InvasionofLorwyn (BG4)
    5961 ElvishVatkeeper (BG1)
    6130 CutShort (W2)
    6250 InfectedDefector (W4)
    6250 InfectedDefector (W4)
    7484 EtchedHostDoombringer (B4)
    7677 AetherbladeAgent (B1)
    9165 RealmbreakersGrasp (W1)
    9280 CompleatedHuntmaster (B2)
    9547 FailedConversion (B4)
   10089 NornsInquisitor (W1)
   10916 MonasteryMentor (W2)
   11069 DeadlyDerision (BB2)
   11069 DeadlyDerision (BB2)
   11547 SculptedPerfection (WB2)
   11961 PhyrexianAwakening (W2)
   12361 InvasionofBelenon (W2)
   14765 DranaandLinvala (WWB1)

*/
