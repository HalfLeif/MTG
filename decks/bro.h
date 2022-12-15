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
};

/*
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

Score: 95.6 (113.0 - 17.4)
Iteration: 128
Lands { B=8 R=9 }
    2601 GoblinBlastRunner (R)
    3047 PowerstoneFracture (B1)
    3151 TerisianMindbreaker (7)
    3189 CombatCourier (1)
    3611 WhirlingStrike (R1)
    3825 CoastalBulwark (2)
    4362 RazetotheGround (R2)
    4362 RazetotheGround (R2)
    4508 EnergyRefractor (2)
    4508 EnergyRefractor (2)
    5057 NoOneLeftBehind (B4)
    5134 BlitzAutomaton (R2)
    5134 BlitzAutomaton (R2)
    5771 UnleashShell (RR3)
    5771 UnleashShell (RR3)
    5864 TransmograntsCrown (2)
    6130 JunkyardGenius (BR1)
    6164 MishrasCommand (R2)
    7084 ExcavationExplosion (R2)
    7084 ExcavationExplosion (R2)
    7265 ScrapworkRager (4)
    7519 TrenchStalker (B4)
    8310 SimianSimulacrum (3)

Score: 95.4 (112.6 - 17.2)
Iteration: 149
Lands { R=9 U=6 }
    2155 UrzasRebuff (UU1)
    2495 WeakstonesSubjugation (U)
    2961 BitterReunion (R1)
    3239 SymmetryMatrix (4)
    3246 CoastalBulwark (2)
    3281 CombatCourier (1)
    3619 WhirlingStrike (R1)
    4078 EnergyRefractor (2)
    4078 EnergyRefractor (2)
    4339 RazetotheGround (R2)
    4339 RazetotheGround (R2)
    4539 ZephyrSentinel (U1)
    4609 BlitzAutomaton (R2)
    4609 BlitzAutomaton (R2)
    4858 WingCommando (U2)
    4858 WingCommando (U2)
    5356 UnleashShell (RR3)
    5356 UnleashShell (RR3)
    5587 TransmograntsCrown (2)
    6429 SpotterThopter (U3)
    6430 MishrasCommand (R2)
    6755 ScrapworkRager (4)
    6830 ExcavationExplosion (R2)
    6830 ExcavationExplosion (R2)
    7480 SimianSimulacrum (3)

Score: 94.4 (111.6 - 17.3)
Iteration: 25
Lands { B=6 R=10 }
    2294 TerisianMindbreaker (7)
    2321 SwiftgearDrake (5)
    2615 PowerstoneFracture (B1)
    2834 GixianSkullflayer (B2)
    2940 MonasterySwiftspear (R)
    3013 TowerWorker (3)
    3238 CombatCourier (1)
    3892 CoastalBulwark (2)
    4296 EnergyRefractor (2)
    4296 EnergyRefractor (2)
    4387 NoOneLeftBehind (B4)
    4915 RazetotheGround (R2)
    5215 BlitzAutomaton (R2)
    5215 BlitzAutomaton (R2)
    5563 UnleashShell (RR3)
    5563 UnleashShell (RR3)
    5799 TransmograntsCrown (2)
    6047 JunkyardGenius (BR1)
    6177 MishrasCommand (R2)
    6510 TrenchStalker (B4)
    7030 ExcavationExplosion (R2)
    7030 ExcavationExplosion (R2)
    7309 ScrapworkRager (4)
    7798 SimianSimulacrum (3)

Score: 94.3 (111.3 - 17.0)
Iteration: 30
Lands { B=7 R=10 }
    2861 TerisianMindbreaker (7)
    3046 PowerstoneFracture (B1)
    3167 GixianSkullflayer (B2)
    3181 CombatCourier (1)
    3312 BitterReunion (R1)
    3907 DisciplesofGix (BB4)
    4067 WhirlingStrike (R1)
    4403 StoneRetrievalUnit (4)
    4510 RazetotheGround (R2)
    4510 RazetotheGround (R2)
    4515 EnergyRefractor (2)
    4515 EnergyRefractor (2)
    5269 BlitzAutomaton (R2)
    5269 BlitzAutomaton (R2)
    5729 UnleashShell (RR3)
    6111 TransmograntsCrown (2)
    6284 MishrasCommand (R2)
    6533 JunkyardGenius (BR1)
    6922 ExcavationExplosion (R2)
    6922 ExcavationExplosion (R2)
    7193 TrenchStalker (B4)
    7288 ScrapworkRager (4)
    7844 SimianSimulacrum (3)

Score: 94.2 (110.8 - 16.7)
Iteration: 53
Lands { B=8 R=8 }
    1975 VeteransPowerblade (3)
    2332 TerisianMindbreaker (7)
    2535 GoblinBlastRunner (R)
    2756 SlagstoneRefinery (4)
    3345 CombatCourier (1)
    3472 CarrionLocust (B2)
    3511 CoastalBulwark (2)
    3516 WhirlingStrike (R1)
    4477 RazetotheGround (R2)
    4477 RazetotheGround (R2)
    4588 NoOneLeftBehind (B4)
    4664 EnergyRefractor (2)
    4664 EnergyRefractor (2)
    5105 BlitzAutomaton (R2)
    5105 BlitzAutomaton (R2)
    5393 UnleashShell (RR3)
    5534 TransmograntsCrown (2)
    6000 MishrasCommand (R2)
    6806 JunkyardGenius (BR1)
    6822 ExcavationExplosion (R2)
    6822 ExcavationExplosion (R2)
    6869 TrenchStalker (B4)
    7630 ScrapworkRager (4)
    7685 SimianSimulacrum (3)

Score: 91.4 (107.7 - 16.3)
Iteration: 101
Lands { U=9 W=6 }
    2780 Curate (U1)
    2780 Curate (U1)
    2899 WeakstonesSubjugation (U)
    2899 WeakstonesSubjugation (U)
    3328 CombatCourier (1)
    3350 ThopterArchitect (W3)
    3503 TowerWorker (3)
    3552 WarlordsElite (W2)
    3755 UrzasRebuff (UU1)
    3775 CoastalBulwark (2)
    3886 ScatterRay (U1)
    3932 SymmetryMatrix (4)
    4207 KoilosRoc (U4)
    4294 AeronautCavalry (W4)
    4301 EnergyRefractor (2)
    4301 EnergyRefractor (2)
    4553 InvoluntaryCooldown (U3)
    5418 ZephyrSentinel (U1)
    5647 WingCommando (U2)
    5647 WingCommando (U2)
    5886 SpotterThopter (U3)
    5985 TransmograntsCrown (2)
    6484 ScrapworkRager (4)
    7886 SimianSimulacrum (3)
    8530 UrzaPrinceofKroog (WU2)

*/
