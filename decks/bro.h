#pragma once

#include <string_view>
#include <vector>

#include "../core/sealed_deck.h"

// Brother's war (2023)
class Bro : public SealedDeck {
public:
  std::string_view data_path() const override { return "data/bro/cards.csv"; }

  std::vector<std::string_view> cards() const override {
    return {
        // 1
        "UrzaPrinceofKroog",
        "ArbalestEngineers",
        "GixianSkullflayer",
        "PowerstoneFracture",
        "TrenchStalker",
        "SymmetryMatrix",
        "BlitzAutomaton",
        "ObstinateBaloth",
        "WastefulHarvest",
        "AeronautCavalry",
        "CoastalBulwark",
        "PowerstoneEngineer",
        "EnergyRefractor",
        "UnionoftheThirdPath",
        // 2
        "TransmograntsCrown",
        "WingCommando",
        "MilitaryDiscipline",
        "NoOneLeftBehind",
        "ScatterRay",
        "JunkyardGenius",
        "ArgothianSprite",
        "Curate",
        "UnleashShell",
        "TowerWorker",
        "RazetotheGround",
        "TawnossTinkering",
        "DredgingClaw",
        "ArmsRace",
        // 3
        "MishrasCommand",
        "AlloyAnimist",
        "HerooftheDunes",
        "ZephyrSentinel",
        "MomentofDefiance",
        "PowerstoneFracture",
        "UrzasRebuff",
        "WingCommando",
        "ExcavationExplosion",
        "UnleashShell",
        "GaeasGift",
        "MilitaryDiscipline",
        "BurrowingRazormaw",
        "VeteransPowerblade",
        // 4
        "TerisianMindbreaker",
        "Audacity",
        "WhirlingStrike",
        "WeakstonesSubjugation",
        "KoilosRoc",
        // "Brushland",
        "EpicConfrontation",
        "ScrapworkRager",
        "BitterReunion",
        "WarlordsElite",
        "SwiftgearDrake",
        "VeteransPowerblade",
        "SpotterThopter",
        "SlagstoneRefinery",
        // 5
        "MomentofDefiance",
        "BurrowingRazormaw",
        "ExcavationExplosion",
        "DeadlyRiposte",
        "WeakstonesSubjugation",
        "CarrionLocust",
        "CitanulStalwart",
        "StoneRetrievalUnit",
        "GoblinBlastRunner",
        "MonasterySwiftspear",
        "MeticulousExcavation",
        "DisciplesofGix",
        "SimianSimulacrum",
        // 6
        "WastefulHarvest",
        "BlitzAutomaton",
        "PowerstoneEngineer",
        "Curate",
        "DredgingClaw",
        "TawnossTinkering",
        "CombatCourier",
        "EnergyRefractor",
        "RazetotheGround",
        "InvoluntaryCooldown",
        // "DemolitionField",
        // "BattlefieldForge",
        // "TocasiasDigSite",
        "ThopterArchitect",
    };
  }

  int MinColors() const override { return 2; }
  int MaxColors() const override { return 3; }

  // Colors the generator can use for building a deck.
  std::vector<Color> AvailableColors() const override {
    return {
        // Color::Black,
        Color::White,
        // Color::Green,
        Color::Blue,
        Color::Red,
    };
  }
};

/*
Score: 98.8 (114.7 - 15.9)
Iteration: 75
Lands { B=6 R=11 }
    2205 SlagstoneRefinery (4)
    2985 CombatCourier (1)
    3497 TerisianMindbreaker (7)
    3661 DisciplesofGix (BB4)
    3744 WhirlingStrike (R1)
    4215 StoneRetrievalUnit (4)
    4233 EnergyRefractor (2)
    4233 EnergyRefractor (2)
    4256 RazetotheGround (R2)
    4256 RazetotheGround (R2)
    4597 NoOneLeftBehind (B4)
    5150 BlitzAutomaton (R2)
    5150 BlitzAutomaton (R2)
    5909 TransmograntsCrown (2)
    6005 JunkyardGenius (BR1)
    6046 UnleashShell (RR3)
    6046 UnleashShell (RR3)
    6342 MishrasCommand (R2)
    6699 ScrapworkRager (4)
    7104 ExcavationExplosion (R2)
    7104 ExcavationExplosion (R2)
    7649 TrenchStalker (B4)
    8330 SimianSimulacrum (3)

Score: 97.9 (114.2 - 16.2)
Iteration: 118
Lands { B=7 R=8 }
    2702 PowerstoneFracture (B1)
    2801 MonasterySwiftspear (R)
    2861 GixianSkullflayer (B2)
    3042 DisciplesofGix (BB4)
    3351 CombatCourier (1)
    3446 CoastalBulwark (2)
    3558 MomentofDefiance (B2)
    3623 WhirlingStrike (R1)
    4183 EnergyRefractor (2)
    4183 EnergyRefractor (2)
    4338 RazetotheGround (R2)
    4338 RazetotheGround (R2)
    4390 StoneRetrievalUnit (4)
    4960 UnleashShell (RR3)
    4960 UnleashShell (RR3)
    5045 BlitzAutomaton (R2)
    5045 BlitzAutomaton (R2)
    5808 TransmograntsCrown (2)
    6067 JunkyardGenius (BR1)
    6450 MishrasCommand (R2)
    6538 TrenchStalker (B4)
    6552 ExcavationExplosion (R2)
    6552 ExcavationExplosion (R2)
    7015 ScrapworkRager (4)
    7511 SimianSimulacrum (3)

Score: 97.2 (113.7 - 16.5)
Iteration: 97
Lands { B=5 R=11 }
    1701 SlagstoneRefinery (4)
    2823 MonasterySwiftspear (R)
    3247 BitterReunion (R1)
    3268 CombatCourier (1)
    3317 SymmetryMatrix (4)
    3743 WhirlingStrike (R1)
    4157 StoneRetrievalUnit (4)
    4176 RazetotheGround (R2)
    4176 RazetotheGround (R2)
    4374 EnergyRefractor (2)
    4374 EnergyRefractor (2)
    4486 NoOneLeftBehind (B4)
    5142 BlitzAutomaton (R2)
    5142 BlitzAutomaton (R2)
    5542 TransmograntsCrown (2)
    5915 UnleashShell (RR3)
    5915 UnleashShell (RR3)
    5941 JunkyardGenius (BR1)
    6126 MishrasCommand (R2)
    6461 TrenchStalker (B4)
    6895 ScrapworkRager (4)
    7355 ExcavationExplosion (R2)
    7355 ExcavationExplosion (R2)
    7575 SimianSimulacrum (3)

Score: 96.5 (113.9 - 17.5)
Iteration: 123
Lands { B=7 R=9 }
    2602 TerisianMindbreaker (7)
    2812 DredgingClaw (2)
    2914 MonasterySwiftspear (R)
    3221 MomentofDefiance (B2)
    3251 CombatCourier (1)
    3488 WhirlingStrike (R1)
    3984 StoneRetrievalUnit (4)
    4242 RazetotheGround (R2)
    4242 RazetotheGround (R2)
    4328 EnergyRefractor (2)
    4328 EnergyRefractor (2)
    4528 NoOneLeftBehind (B4)
    4889 BlitzAutomaton (R2)
    4889 BlitzAutomaton (R2)
    5285 UnleashShell (RR3)
    5285 UnleashShell (RR3)
    5884 TransmograntsCrown (2)
    6025 MishrasCommand (R2)
    6518 JunkyardGenius (BR1)
    6787 TrenchStalker (B4)
    7126 ExcavationExplosion (R2)
    7126 ExcavationExplosion (R2)
    7190 ScrapworkRager (4)
    7780 SimianSimulacrum (3)


Score: 96.3 (112.8 - 16.4)
Iteration: 111
Lands { B=6 R=10 }
    2607 SwiftgearDrake (5)
    2786 DredgingClaw (2)
    2818 MonasterySwiftspear (R)
    3155 MomentofDefiance (B2)
    3155 MomentofDefiance (B2)
    3536 CombatCourier (1)
    3743 WhirlingStrike (R1)
    4235 EnergyRefractor (2)
    4235 EnergyRefractor (2)
    4422 StoneRetrievalUnit (4)
    4512 RazetotheGround (R2)
    4512 RazetotheGround (R2)
    5189 BlitzAutomaton (R2)
    5189 BlitzAutomaton (R2)
    5738 UnleashShell (RR3)
    5738 UnleashShell (RR3)
    6019 TransmograntsCrown (2)
    6253 JunkyardGenius (BR1)
    6257 MishrasCommand (R2)
    6476 ScrapworkRager (4)
    6820 ExcavationExplosion (R2)
    6820 ExcavationExplosion (R2)
    6987 TrenchStalker (B4)
    7506 SimianSimulacrum (3)

Score: 95.9 (112.0 - 16.2)
Iteration: 92
Lands { R=10 U=5 }
    2002 ArmsRace (R3)
    2384 WeakstonesSubjugation (U)
    2884 MonasterySwiftspear (R)
    3136 BitterReunion (R1)
    3184 CombatCourier (1)
    3412 CoastalBulwark (2)
    3627 WhirlingStrike (R1)
    3815 StoneRetrievalUnit (4)
    4015 ZephyrSentinel (U1)
    4210 EnergyRefractor (2)
    4210 EnergyRefractor (2)
    4500 RazetotheGround (R2)
    4500 RazetotheGround (R2)
    4563 WingCommando (U2)
    4997 BlitzAutomaton (R2)
    4997 BlitzAutomaton (R2)
    5419 UnleashShell (RR3)
    5419 UnleashShell (RR3)
    5811 SpotterThopter (U3)
    5839 TransmograntsCrown (2)
    6594 MishrasCommand (R2)
    6915 ExcavationExplosion (R2)
    6915 ExcavationExplosion (R2)
    7028 ScrapworkRager (4)
    7897 SimianSimulacrum (3)

Score: 93.5 (110.0 - 16.4)
Iteration: 144
Lands { R=11 W=6 }
    2651 TerisianMindbreaker (7)
    3115 MonasterySwiftspear (R)
    3319 CombatCourier (1)
    3358 BitterReunion (R1)
    3444 TowerWorker (3)
    3646 CoastalBulwark (2)
    3803 WhirlingStrike (R1)
    4472 EnergyRefractor (2)
    4472 EnergyRefractor (2)
    4567 RazetotheGround (R2)
    4567 RazetotheGround (R2)
    4641 StoneRetrievalUnit (4)
    5101 AeronautCavalry (W4)
    5462 BlitzAutomaton (R2)
    5462 BlitzAutomaton (R2)
    5767 TransmograntsCrown (2)
    6205 UnleashShell (RR3)
    6205 UnleashShell (RR3)
    6507 MishrasCommand (R2)
    7046 ExcavationExplosion (R2)
    7046 ExcavationExplosion (R2)
    7401 ScrapworkRager (4)
    8297 SimianSimulacrum (3)

Score: 93.2 (110.8 - 17.6)
Iteration: 53
Lands { R=7 U=6 W=4 }
    2839 WarlordsElite (W2)
    2937 TerisianMindbreaker (7)
    3163 TowerWorker (3)
    3164 CombatCourier (1)
    3850 CoastalBulwark (2)
    3987 KoilosRoc (U4)
    4052 SymmetryMatrix (4)
    4464 EnergyRefractor (2)
    4464 EnergyRefractor (2)
    4615 BlitzAutomaton (R2)
    4615 BlitzAutomaton (R2)
    4674 ZephyrSentinel (U1)
    4890 UnleashShell (RR3)
    4890 UnleashShell (RR3)
    5211 WingCommando (U2)
    5861 TransmograntsCrown (2)
    6024 SpotterThopter (U3)
    6194 MishrasCommand (R2)
    6795 UrzaPrinceofKroog (WU2)
    6923 ExcavationExplosion (R2)
    6923 ExcavationExplosion (R2)
    7488 ScrapworkRager (4)
    7669 SimianSimulacrum (3)


*/
