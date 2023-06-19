#pragma once

#include <string_view>
#include <vector>

#include "../core/sealed_deck.h"

// March of the Machine (2023)
class Mom : public SealedDeck {
public:
  std::string_view data_path() const override { return "data/mom/cards.csv"; }

  int MinColors() const override { return 3; }
  int MaxColors() const override { return 4; }

  std::vector<Color> AvailableColors() const override {
    return {
        Color::Black, Color::White, Color::Green, Color::Blue, Color::Red,
    };
  }

  std::vector<std::string_view> forced_cards() const override {
    return {
        "ZurgoandOjutai",
        // "MonasteryMentor",    "KamiofWhisperedHopes", "ElvishVatkeeper",
        // "PhyrexianAwakening", "SculptedPerfection",   "DeadlyDerision",
        // "DeadlyDerision",     "InvasionofLorwyn",
        // "InvasionofShandalar",
    };
  }

  std::vector<std::string_view> cards() const override {
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
        "EtchedHostDoombringer",
        "FailedConversion",
        "InvasionofLorwyn",
        "GloomfangMauler",
        //
        "IchorDrinker",
        "KamiofWhisperedHopes",
        "NezumiFreewheeler",
        "InvasionofShandalar",
        "RenderInert",
        "KithkinBillyrider",
        "RonaSheoldredsFaithful",
        "BladedBattleFan",
        "DaxosBlessedbytheSun",
        "CorruptedConviction",
        "ConsumingAetherborn",
        "ConsumingAetherborn",
        "KwendePrideofFemeref",
        "KorHalberd",
        "KorHalberd",
        "Scrollshift",
        "InspiredCharge",
        "Kitesail",
        "OvergrownPest",
        "SandstalkerMoloch",
        "KnightoftheNewCoalition",
        "WarHistorian",
        "WarHistorian",
        "HidetsuguandKairi",
        "RankleandTorbran",
        "AtraxaPraetorsVoice",
        "JeganthatheWellspring",
        "BlightedBurgeoning",
        "TimberlandAncient",
        "WaryThespian",
        "WaryThespian",
        "SerpentBladeAssailant",
        "FynntheFangbearer",
        "WildwoodEscort",
        "BondedHerdbeast",
        "ImotiCelebrantofBounty",
        //
        "VolcanicSpite",
        "FurtiveAnalyst",
        "BeamtownBeatstick",
        "OmenHawker",
        "ExpeditionLookout",
        "AstralWingspan",
        "CorruptionofTowashi",
        "HaloChargedSkaab",
        "HaloChargedSkaab",
        "InvasionofPyrulea",
        "HaloForager",
        "ZhalfirinShapecraft",
        "ZhalfirinShapecraft",
        "FurnaceHostCharger",
        "AkkiScrapchomper",
        //
        "ThrashingFrontliner",
        "WarTrainedSlasher",
        "Negate",
        "ArtisticRefusal",
        "KhenraSpellspear",
        "HarriedArtisan",
        "ZurgoandOjutai",
        "InvasionofMercadia",
        "CityonFire",
        "StasisField",
        "PreeningChampion",
        "PreeningChampion",
        "ShivanBranchBurner",
        "OrderoftheMirror",
        "VolcanicSpite",
        "InvasionofRegatha",
        "MomentofTruth",
        "ChangetheEquation",
        "FearlessSkald",
        "AssimilateEssence",
        "EyesofGitaxias",
        "InvasionofSegovia",
        "OculusWhelp",
        // Round 3
        "WrennsResolve",
        "MeetingofMinds",
        "EnduringBondwarden",
        "AtraxasFall",
        "VengeantEarth",
        "FlywheelRacer",
        "FinalFlourish",
        "InspiredCharge",
        "ScrappyBruiser",
        "MirrorShieldHoplite",
        "PolukranosReborn",
        "InvasionofKamigawa",
        "AegartheFreezingFlame",
        "TangledSkyline",
    };
  }

  std::vector<std::string_view> chosen_deck() const override {
    return RUW_chosen_deck();
  }

  std::vector<std::string_view> RUW_chosen_deck() const {
    // Lands: R8 U7 W2
    return {
        "VolcanicSpite",     //
        "VolcanicSpite",     //
        "StasisField",       //
        "AssimilateEssence", // <- "Negate",
        "ArtisticRefusal",   //
        // "CutShort", //

        // "MomentofTruth",     // <- "CityonFire",
        "BeamtownBeatstick", //
        "AstralWingspan",    //

        // "ThrashingFrontliner",
        "KhenraSpellspear",   //
        "InvasionofMercadia", //
        "OrderoftheMirror",   //
        "ThrashingFrontliner",

        "InvasionofRegatha", //
        "PreeningChampion",  //
        "PreeningChampion",  //
        "HarriedArtisan",    //
        "InvasionofSegovia", //

        "InvasionofKamigawa", //<- "EyesofGitaxias",    //
        "WarTrainedSlasher",  //
        "OculusWhelp",        // <- "HaloChargedSkaab",   //
        "FearlessSkald",      //
        "HaloChargedSkaab",   // <- "CorruptionofTowashi",

        "ZurgoandOjutai",     //
        "ShivanBranchBurner", //

    };
  }

  std::vector<std::string_view> WBG_chosen_deck() const {
    return {
        "SurgeofSalvation",
        "AngelicIntervention",
        "IchorDrinker",
        // <- "TarkirDuneshaper",
        "AetherbladeAgent",
        "NornsInquisitor",
        "MonasteryMentor",
        "RealmbreakersGrasp",
        "ElvishVatkeeper",
        "CompleatedHuntmaster",
        "KamiofWhisperedHopes",
        // <- "InvasionofBelenon",
        "PhyrexianAwakening",
        "NezumiFreewheeler",
        // <- "KithkinBillyrider",
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

Summary

W
bonus: 4.51956
num_above: 11
num_below: 13

U
bonus: 7.83489
num_above: 16
num_below: 12

B
bonus: 4.87467
num_above: 13
num_below: 11

R
bonus: 5.56956
num_above: 10
num_below: 7

G
bonus: 2.632
num_above: 8
num_below: 11

Best cards
        spell WUR2 ZurgoandOjutai #19
        spell WWB1 DranaandLinvala #44
        spell WUBG AtraxaPraetorsVoice #62
        spell BBRR1 RankleandTorbran #64
        spell UUB2 HidetsuguandKairi #67
        spell UB1 HaloForager #69
        spell R1 KhenraSpellspear #71
        spell R2 HarriedArtisan #73
        spell BG1 ElvishVatkeeper #78
        spell W1 NornsInquisitor #87
        spell U2 InvasionofSegovia #88
        spell R4 JeganthatheWellspring #104
        spell UU4 ArtisticRefusal #107
        spell G2 KamiofWhisperedHopes #108
        spell W2 InvasionofBelenon #115
        spell R1 VolcanicSpite #119
        spell R1 VolcanicSpite #119
        spell W2 PhyrexianAwakening #120
        spell GG1 SandstalkerMoloch #123
        spell UG InvasionofPyrulea #125
        spell R2 InvasionofRegatha #130
        spell U4 CorruptionofTowashi #134
        spell U2 PreeningChampion #135
        spell U2 PreeningChampion #135
        spell W1 RealmbreakersGrasp #136
        spell W2 MonasteryMentor #143
        spell G1 FynntheFangbearer #147
        spell U2 EyesofGitaxias #152
        spell U4 HaloChargedSkaab #156
        spell U4 HaloChargedSkaab #156

# Round 2

75.1 (97.1 - 22.0) Lands { B=9 G=2 W=5 WG=1 }
75.3 (97.6 - 22.3) Lands { B=7 G=4 W=5 WG=1 }
75.5 (98.0 - 22.5) Lands { B=6 G=3 W=7 WG=1 }
75.7 (96.7 - 20.9) Lands { B=8 G=1 W=7 WG=1 }
75.8 (97.8 - 21.9) Lands { B=7 G=3 W=6 WG=1 }
76.8 (98.0 - 21.2) Lands { B=7 G=2 W=7 WG=1 }
76.8 (97.0 - 20.2) Lands { B=7 G=1 W=8 WG=1 }
76.9 (98.1 - 21.3) Lands { B=8 G=3 W=5 WG=1 }
77.1 (97.5 - 20.4) Lands { B=9 G=1 W=6 WG=1 }
78.5 (98.7 - 20.2) Lands { B=8 G=2 W=6 WG=1 }

    4699 GloomfangMauler (BB5)
    5032 SurgeofSalvation (W)
    6080 IchorDrinker (B)
    6191 AngelicIntervention (W1)
    6437 CutShort (W2)
    7640 KamiofWhisperedHopes (G2)
    7685 InfectedDefector (W4)
    7685 InfectedDefector (W4)
    8355 NezumiFreewheeler (B3)
    8416 AetherbladeAgent (B1)
    8552 InvasionofLorwyn (BG4)
    8591 RealmbreakersGrasp (W1)
    8622 ElvishVatkeeper (BG1)
    9266 EtchedHostDoombringer (B4)
    9361 NornsInquisitor (W1)
   10032 CompleatedHuntmaster (B2)
   10876 MonasteryMentor (W2)
   10909 FailedConversion (B4)
   11699 PhyrexianAwakening (W2)
   11785 SculptedPerfection (WB2)
   11859 DeadlyDerision (BB2)
   11859 DeadlyDerision (BB2)
   13327 DranaandLinvala (WWB1)

# Round 1

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

72.2 (91.9 - 19.7) base Lands { B=6 G=2 W=8 WG=1 }
72.4 (91.9 - 19.6) base Lands { B=8 G=1 W=7 WG=1 }
72.4 (92.2 - 19.8) exp Lands { B=6 G=2 W=8 WG=1 }
72.6 (92.1 - 19.5) base Lands { B=7 G=2 W=7 WG=1 }
72.8 (91.8 - 19.1) base Lands { B=7 G=1 W=8 WG=1 }
72.8 (92.4 - 19.6) exp Lands { B=8 G=1 W=7 WG=1 }
73.2 (92.3 - 19.1) exp Lands { B=6 G=1 W=9 WG=1 }
73.4 (92.6 - 19.2) exp Lands { B=7 G=1 W=8 WG=1 }
73.6 (92.2 - 18.6) exp Lands { B=8 W=8 WG=1 }
74.4 (93.4 - 19.0) exp Lands { B=7 G=2 W=7 WG=1 }

    4050 GloomfangMauler (BB5)
    4696 KithkinBillyrider (W2)
    5360 AngelicIntervention (W1)
    5432 SurgeofSalvation (W)
    5832 InfectedDefector (W4)
    5832 InfectedDefector (W4)
    6110 CutShort (W2)
    6215 DaxosBlessedbytheSun (WW)
    7287 EtchedHostDoombringer (B4)
    7713 InvasionofLorwyn (BG4)
    7955 AetherbladeAgent (B1)
    8375 ElvishVatkeeper (BG1)
    8727 RealmbreakersGrasp (W1)
    9584 FailedConversion (B4)
    9753 CompleatedHuntmaster (B2)
    9842 DeadlyDerision (BB2)
    9842 DeadlyDerision (BB2)
    9985 NornsInquisitor (W1)
   10922 MonasteryMentor (W2)
   11442 SculptedPerfection (WB2)
   11789 PhyrexianAwakening (W2)
   13046 InvasionofBelenon (W2)
   14852 DranaandLinvala (WWB1)

Score: 88.2 (106.1 - 17.9)
Iteration: 20
Lands { R=8 U=9 }
    2394 ShivanBranchBurner (RR5)
    2634 MomentofTruth (U1)
    2958 StasisField (U1)
    3070 FearlessSkald (R4)
    3109 WarTrainedSlasher (R3)
    3242 BeamtownBeatstick (R)
    3638 OrderoftheMirror (U1)
    3641 InvasionofMercadia (R1)
    4560 VolcanicSpite (R1)
    4560 VolcanicSpite (R1)
    5071 EyesofGitaxias (U2)
    5216 KhenraSpellspear (R1)
    5236 AstralWingspan (U4)
    5478 HaloChargedSkaab (U4)
    5478 HaloChargedSkaab (U4)
    5896 InvasionofRegatha (R2)
    5898 PreeningChampion (U2)
    5898 PreeningChampion (U2)
    6076 ArtisticRefusal (UU4)
    6348 InvasionofSegovia (U2)
    6460 CorruptionofTowashi (U4)
    6606 HarriedArtisan (R2)
    7961 JeganthatheWellspring (R4)

# Forcing Ojutai

Score: 87.6 (110.2 - 22.6)
Iteration: 133
Lands { R=7 U=7 W=4 }
    2666 MomentofTruth (U1)
    3228 ZhalfirinShapecraft (U1) -> StasisField
    3288 OculusWhelp (U3) -> ShivanBranchBurner
    3653 InvasionofMercadia (R1)
    4061 MonasteryMentor (W2)
    4389 VolcanicSpite (R1)
    4389 VolcanicSpite (R1)
    4488 EyesofGitaxias (U2)
    4967 PhyrexianAwakening (W2) -> Cut short
    5148 KhenraSpellspear (R1)
    5380 AstralWingspan (U4)
    5645 InvasionofRegatha (R2)
    5801 PreeningChampion (U2)
    5801 PreeningChampion (U2)
    5953 HaloChargedSkaab (U4)
    5953 HaloChargedSkaab (U4)
    6511 ArtisticRefusal (UU4)
    6600 HarriedArtisan (R2)
    6627 CorruptionofTowashi (U4)
    6735 InvasionofSegovia (U2)
    6959 JeganthatheWellspring (R4)
    7602 ZurgoandOjutai (WUR2)

# Others

Score: 86.4 (104.7 - 18.3)
Iteration: 143
Lands { U=9 W=9 }
    2138 KithkinBillyrider (W2)
    2680 StasisField (U1)
    2748 OmenHawker (U)
    2998 DaxosBlessedbytheSun (WW)
    3795 KwendePrideofFemeref (W3)
    3880 OrderoftheMirror (U1)
    4109 RealmbreakersGrasp (W1)
    4406 EyesofGitaxias (U2)
    5154 MonasteryMentor (W2)
    5178 PreeningChampion (U2)
    5178 PreeningChampion (U2)
    5201 NornsInquisitor (W1)
    5532 AstralWingspan (U4)
    5797 PhyrexianAwakening (W2)
    6051 HaloChargedSkaab (U4)
    6051 HaloChargedSkaab (U4)
    6550 InvasionofBelenon (W2)
    6550 InvasionofBelenon (W2)
    6706 KnightoftheNewCoalition (W3)
    6797 ArtisticRefusal (UU4)
    7075 InvasionofSegovia (U2)
    7264 CorruptionofTowashi (U4)

Score: 86.1 (104.8 - 18.7)
Iteration: 67
Lands { B=8 U=9 }
    2637 MomentofTruth (U1)
    2696 OmenHawker (U)
    2769 CorruptedConviction (B)
    2843 EtchedHostDoombringer (B4)
    2850 ConsumingAetherborn (B3)
    3115 AssimilateEssence (U1)
    3649 NezumiFreewheeler (B3)
    3893 OrderoftheMirror (U1)
    3951 AetherbladeAgent (B1)
    4952 CompleatedHuntmaster (B2)
    5040 AstralWingspan (U4)
    5184 EyesofGitaxias (U2)
    5483 HaloChargedSkaab (U4)
    5483 HaloChargedSkaab (U4)
    5615 DeadlyDerision (BB2)
    5615 DeadlyDerision (BB2)
    5644 PreeningChampion (U2)
    5644 PreeningChampion (U2)
    6191 ArtisticRefusal (UU4)
    6495 HaloForager (UB1)
    6495 CorruptionofTowashi (U4)
    6514 InvasionofSegovia (U2)
    7309 HidetsuguandKairi (UUB2)

Score: 79.8 (97.7 - 17.9)
Iteration: 68
Lands { B=6 W=9 }
    2140 KithkinBillyrider (W2)
    2304 KorHalberd (W)
    2369 CorruptedConviction (B)
    2547 Scrollshift (W2)
    2647 SurgeofSalvation (W)
    2677 ConsumingAetherborn (B3)
    2710 IchorDrinker (B)
    2727 AngelicIntervention (W1)
    3175 InfectedDefector (W4)
    3230 DaxosBlessedbytheSun (WW)
    3429 NezumiFreewheeler (B3)
    3525 AetherbladeAgent (B1)
    4237 FailedConversion (B4)
    4301 DeadlyDerision (BB2)
    4301 DeadlyDerision (BB2)
    4599 RealmbreakersGrasp (W1)
    4658 CompleatedHuntmaster (B2)
    5307 MonasteryMentor (W2)
    5356 NornsInquisitor (W1)
    5673 KnightoftheNewCoalition (W3)
    5690 SculptedPerfection (WB2)
    5968 InvasionofBelenon (W2)
    5968 InvasionofBelenon (W2)
    6050 PhyrexianAwakening (W2)
    7361 DranaandLinvala (WWB1)

Score: 79.8 (96.5 - 16.7)
Iteration: 67
Lands { G=8 W=8 }
    1872 KithkinBillyrider (W2)
    2267 Kitesail (2)
    2671 SurgeofSalvation (W)
    2749 SerpentBladeAssailant (G2)
    2767 InfectedDefector (W4)
    2888 BlightedBurgeoning (G2)
    2998 DaxosBlessedbytheSun (WW)
    3224 WaryThespian (G1)
    3452 BondedHerdbeast (G4)
    3552 TimberlandAncient (GG4)
    4084 FynntheFangbearer (G1)
    4251 OvergrownPest (G2)
    4398 KwendePrideofFemeref (W3)
    4641 RealmbreakersGrasp (W1)
    4731 InvasionofShandalar (GG3)
    4953 SandstalkerMoloch (GG1)
    4967 WildwoodEscort (G4)
    5162 NornsInquisitor (W1)
    5253 MonasteryMentor (W2)
    5990 InvasionofBelenon (W2)
    5990 InvasionofBelenon (W2)
    6043 PhyrexianAwakening (W2)
    6339 KnightoftheNewCoalition (W3)
    6426 KamiofWhisperedHopes (G2)

Score: 77.3 (95.5 - 18.2)
Iteration: 146
Lands { B=8 W=9 }
    2260 KorHalberd (W)
    2468 ConsumingAetherborn (B3)
    2556 TarkirDuneshaper (W)
    2673 SurgeofSalvation (W)
    2812 CorruptedConviction (B)
    2961 InfectedDefector (W4)
    3051 IchorDrinker (B)
    3389 KwendePrideofFemeref (W3)
    3673 EtchedHostDoombringer (B4)
    3673 EtchedHostDoombringer (B4)
    3954 AetherbladeAgent (B1)
    4333 FailedConversion (B4)
    4501 RealmbreakersGrasp (W1)
    4640 CompleatedHuntmaster (B2)
    5150 NornsInquisitor (W1)
    5425 MonasteryMentor (W2)
    5835 DeadlyDerision (BB2)
    5835 DeadlyDerision (BB2)
    5939 KnightoftheNewCoalition (W3)
    5961 PhyrexianAwakening (W2)
    6129 SculptedPerfection (WB2)
    6464 InvasionofBelenon (W2)
    8086 DranaandLinvala (WWB1)

When forcing Shandalar + Phyrexian:

Score: 74.8 (96.2 - 21.4)
Iteration: 103
Lands { B=6 G=4 W=6 }
    1996 InvasionofShandalar (GG3)
    2110 DaxosBlessedbytheSun (WW)
    2465 CorruptedConviction (B)
    2937 IchorDrinker (B)
    3072 OvergrownPest (G2)
    3172 NezumiFreewheeler (B3)
    3379 AetherbladeAgent (B1)
    3622 FynntheFangbearer (G1)
    4232 RealmbreakersGrasp (W1)
    4234 FailedConversion (B4)
    4324 InvasionofLorwyn (BG4)
    4374 CompleatedHuntmaster (B2)
    4401 DeadlyDerision (BB2)
    4401 DeadlyDerision (BB2)
    4417 MonasteryMentor (W2)
    4444 WildwoodEscort (G4)
    4757 NornsInquisitor (W1)
    4902 KamiofWhisperedHopes (G2)
    5082 InvasionofBelenon (W2)
    5254 ElvishVatkeeper (BG1)
    5323 KnightoftheNewCoalition (W3)
    5381 SculptedPerfection (WB2)
    5520 PhyrexianAwakening (W2)
    5654 DranaandLinvala (WWB1)

*/
