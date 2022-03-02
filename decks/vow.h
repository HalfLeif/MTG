#pragma once

#include <string_view>
#include <vector>

#include "../core/sealed_deck.h"

class Vow : public SealedDeck {
public:
  std::string_view data_path() const override { return "data/vow/cards.csv"; }

  std::vector<std::string_view> cards() const override {
    return {
        "Gryffwing Cavalry",
        "Creepy Puppeteer",
        "Groom's Finery",
        "Steelclad Spirit",
        "Gift of Fangs",
        "Heron-Blessed Geist",
        "Skywarp Skaab",
        "Ceremonial Knife",
        "Wedding Security",
        "Overcharged Amalgam",
        "Witness the Future",
        "Rot-Tide Gargantua",
        "Sigarda's Imprisonment",
        "Chill of the Grave",
        "Steelclad Spirit",
        "Bramble Armor",
        "Mischievous Catgeist",
        "Voldaren Bloodcaster",
        "Alluring Suitor",
        "Flourishing Hunter",
        "Flame-Blessed Bolt",
        "Dawnhart Disciple",
        "Rural Recruit",
        "Steelclad Spirit",
        "Radiant Grace",
        "Wedding Announcement",
        "Alluring Suitor",
        "Parish-Blade Trainee",
        "Ceremonial Knife",
        "Toxic Scorpion",
        "Wedding Invitation",
        "Weary Prisoner",
        "Catapult Fodder",
        // "Voldaren Estate", // Land
        "Whispering Wizard",
        "Lantern Bearer",
        "Stitched Assistant",
        "Sanctify",
        "Sigarda's Imprisonment",
        "Wolf Strike",
        "Sanguine Statuette",
        "Katilda, Dawnhart Martyr",
        "Distracting Geist",
        "Pointed Discussion",
        "Steelclad Spirit",
        "Undying Malice",
        "Abrade",
        "Doomed Dissenter",
        "Catapult Fodder",
        "Runo Stromkirk",
        "Restless Bloodseeker",
        "Scattered Thoughts",
        "Blood Petal Celebrant",
        "Persistent Specimen",
        "Traveling Minister",
        "Weary Prisoner",
        "Skulking Killer",
        "Dig Up",
        "Fell Stinger",
        "Diregraf Scavenger",
        "Falkenrath Celebrants",
        "Vampire's Kiss",
        "Binding Geist",
        "Weaver of Blossoms",
        "Radiant Grace",
        "Sorin the Mirthless",
        "Dread Fugue",
        "Courier Bat",
        "Unhallowed Phalanx",
        "Lightning Wolf",
        "Supernatural Rescue",
        "Hookhand Mariner",
        "Arm the Cathars",
        "Mirrorhall Mimic",
        "Edgar's Awakening",
        "Blood Servitor",
        "Gryff Rider",
        "Honored Heirloom",
        "Alchemist's Retrieval",
        "Kessig Flamebreather",

        // Round 2
        "Path of Peril", // Primarily works well with BW
        "Bride's Gown",
        "Lambholt Raconteur",
        "Nature's Embrace",
        "Apprentice Sharpshooter",
        "Nature's Embrace",
        "Bleed Dry",
        "Binding Geist",
        "By Invitation Only",
        "Wolfkin Outcast",
        "Toxic Scorpion",
        "Boarded Window",
        "Gluttonous Guest",
        "Heron of Hope",
        "Snarling Wolf",
        "Diregraf Scavenger",

        // Round 3
        "Sawblade Slinger",
        "Henrika Domnathi",
        "Markov Purifier",
        "Unhallowed Phalanx",
        "Pyre Spawn",
        "Lightning Wolf",
        "Dawnhart Disciple",
        "Flame-Blessed Bolt",
        "Angelic Quartermaster",
        "Savior of Ollenbock",
        "Gutter Skulker",
        "Dreadlight Monstrosity",
        "Wolf Strike",
        "Grisly Ritual",
        "Dawnhart Disciple",
        "Apprentice Sharpshooter",

        // Round 4
        "Lantern of the Lost",
        "Hullbreaker Horror",
        "Vampires' Vengeance",
        "Unholy Officiant",
        "Adamant Will",
        "Fierce Retribution",
        "Witch's Web",
        "Flourishing Hunter",
        "Dormant Grove",
        "Savior of Ollenbock",
        "Boarded Window",
        "Gryff Rider",
        "Estwald Shieldbasher",
        "Adamant Will",
        "Wanderlight Spirit",
        "Hungry Ridgewolf",
    };
  }

  std::vector<std::string_view> forced_cards() const override {
    return {
        "Traveling Minister",       //
        "Markov Purifier",          //
        "Katilda, Dawnhart Martyr", //
        "Wedding Announcement",     //
        "Bleed Dry",                //
        "Sorin the Mirthless",
    };
  }

  std::vector<std::string_view> chosen_deck() const override {
    return {
        "Doomed Dissenter",
        "Restless Bloodseeker",
        "Traveling Minister",
        "Catapult Fodder",
        "Catapult Fodder",
        "Path of Peril",
        "Fierce Retribution",
        "Savior of Ollenbock",
        "Savior of Ollenbock",
        "Voldaren Bloodcaster",
        "Markov Purifier",
        "Rot-Tide Gargantua",
        "Katilda, Dawnhart Martyr",
        "Diregraf Scavenger",
        "Diregraf Scavenger",
        "Fell Stinger",
        "Bleed Dry",
        "Angelic Quartermaster",
        "Gryffwing Cavalry",
        "Wedding Announcement",
        "Henrika Domnathi",
        "By Invitation Only",
        "Sorin the Mirthless",
    };
  }
};

/* R4
Score: 65.4018
Iteration: 96
Lands { W=8 B=9 }
1301.9 Gryff Rider (W2) -> Restless Bloodseeker (B1)
1385.37 Traveling Minister (W)
1659.69 Catapult Fodder (B2)
1659.69 Catapult Fodder (B2)
2139.92 Path of Peril (BB1)
2403.92 Fierce Retribution (W1)
2601.17 Heron of Hope (W3) -> Adamant Will (W1) or Doomed Dissenter (B1)
2720.11 Savior of Ollenbock (WW1)
2720.11 Savior of Ollenbock (WW1)
2814.01 Voldaren Bloodcaster (B1)
2872.47 Markov Purifier (WB1)
3003.52 Rot-Tide Gargantua (BB3)
3065.95 Katilda, Dawnhart Martyr (WW1)
3178.24 Diregraf Scavenger (B3)
3178.24 Diregraf Scavenger (B3)
3271.74 Fell Stinger (B2)
3380.5 Bleed Dry (BB2)
3584.73 Angelic Quartermaster (WW3)
3817.69 Gryffwing Cavalry (W3)
4224.79 Wedding Announcement (W2)
4710.03 Henrika Domnathi (BB2)
4841.94 By Invitation Only (WW3)
4938.06 Sorin the Mirthless (BB2)

Score: 65.3328
Iteration: 92
Lands { W=8 B=10 }
1346.32 Traveling Minister (W)
1479.99 Parish-Blade Trainee (W1)
1567 Courier Bat (B2)
2008.86 Distracting Geist (W2)
2388.62 Savior of Ollenbock (WW1)
2388.62 Savior of Ollenbock (WW1)
2431.41 Fierce Retribution (W1)
2504.91 Heron of Hope (W3)
2978.26 Markov Purifier (WB1)
2992.54 Voldaren Bloodcaster (B1)
3036.39 Katilda, Dawnhart Martyr (WW1)
3084.4 Rot-Tide Gargantua (BB3)
3118.62 Fell Stinger (B2)
3165.42 Diregraf Scavenger (B3)
3165.42 Diregraf Scavenger (B3)
3647.63 Gryffwing Cavalry (W3)
3882.68 Bleed Dry (BB2)
4045.94 Angelic Quartermaster (WW3)
4712.86 Wedding Announcement (W2)
4941.02 Sorin the Mirthless (BB2)
5255.41 By Invitation Only (WW3)
5745.47 Henrika Domnathi (BB2)

Score: 64.1836
Iteration: 105
Lands { W=9 B=8 }
1270.38 Gryff Rider (W2) -> Markov Purifier
1446.65 Traveling Minister (W)
1493.83 Sigarda's Imprisonment (W2)
1985.35 Catapult Fodder (B2)
1985.35 Catapult Fodder (B2)
2174.4 Fierce Retribution (W1)
2306.82 Path of Peril (BB1)
2371.46 Heron of Hope (W3)
2750.08 Rot-Tide Gargantua (BB3)
2836.68 Voldaren Bloodcaster (B1)
2878.11 Savior of Ollenbock (WW1)
2878.11 Savior of Ollenbock (WW1)
3141.97 Katilda, Dawnhart Martyr (WW1)
3181.08 Fell Stinger (B2)
3236.47 Diregraf Scavenger (B3)
3236.47 Diregraf Scavenger (B3)
3343.49 Bleed Dry (BB2)
3597.45 Angelic Quartermaster (WW3)
3943.38 Gryffwing Cavalry (W3)
4196.08 Wedding Announcement (W2)
4653.5 Henrika Domnathi (BB2)
4654.2 Sorin the Mirthless (BB2)
4780.28 By Invitation Only (WW3)

Score: 64.1493
Iteration: 92
Lands { W=10 B=8 }
1418.42 Traveling Minister (W)
1628.76 Courier Bat (B2)
1674.44 Parish-Blade Trainee (W1)
2104.69 Distracting Geist (W2)
2160.06 Fierce Retribution (W1)
2389.4 Markov Purifier (WB1)
2791.34 Voldaren Bloodcaster (B1)
2850.23 Savior of Ollenbock (WW1)
2850.23 Savior of Ollenbock (WW1)
2979.25 Rot-Tide Gargantua (BB3)
2990.58 Heron of Hope (W3)
3066.24 Fell Stinger (B2)
3256.26 Diregraf Scavenger (B3)
3256.26 Diregraf Scavenger (B3)
3615.73 Bleed Dry (BB2)
3680.41 Katilda, Dawnhart Martyr (WW1)
3918.71 Angelic Quartermaster (WW3)
3970.5 Gryffwing Cavalry (W3)
4249.1 Sorin the Mirthless (BB2)
4350.67 Wedding Announcement (W2)
4638.62 Henrika Domnathi (BB2)
4997.9 By Invitation Only (WW3)
*/

/* R3
Score: 62.7984
Iteration: 120
Lands { W=6 B=12 C=1 }
1287.45 Traveling Minister (W)
1490.67 Sigarda's Imprisonment (W2)
1825.08 Restless Bloodseeker (B1)
2035.82 Doomed Dissenter (B1)
2079.26 Gluttonous Guest (B2)
2515.4 Catapult Fodder (B2)
2785.67 Path of Peril (BB1)
3020.18 Markov Purifier (WB1)
3122.9 Voldaren Bloodcaster (B1)
3244.62 Diregraf Scavenger (B3)
3244.62 Diregraf Scavenger (B3)
3247.33 Wedding Security (BB3)
3460.68 Angelic Quartermaster (WW3)
3507.15 Gryffwing Cavalry (W3)
3755.74 Rot-Tide Gargantua (BB3)
3938.84 By Invitation Only (WW3)
4003.04 Fell Stinger (B2)
4345.22 Bleed Dry (BB2)
4480.97 Wedding Announcement (W2)
5144.44 Henrika Domnathi (BB2)
5192.36 Sorin the Mirthless (BB2)

Score: 62.3807
Iteration: 86
Lands { W=7 B=9 C=1 }
1322.29 Traveling Minister (W)
1580.19 Wedding Invitation (2)
1733.41 Parish-Blade Trainee (W1)
1803.86 Catapult Fodder (B2)
1803.86 Catapult Fodder (B2)
2087.31 Edgar's Awakening (BB3)
2262.63 Distracting Geist (W2)
2286.38 Savior of Ollenbock (WW1)
2305.83 Heron of Hope (W3)
2612.97 Markov Purifier (WB1)
2726 Katilda, Dawnhart Martyr (WW1)
2981.95 Rot-Tide Gargantua (BB3)
2995.38 Voldaren Bloodcaster (B1)
3245.78 Diregraf Scavenger (B3)
3245.78 Diregraf Scavenger (B3)
3348.29 Fell Stinger (B2)
3502.03 Angelic Quartermaster (WW3)
3630.55 By Invitation Only (WW3)
3694.46 Gryffwing Cavalry (W3)
3922.33 Bleed Dry (BB2)
4337.42 Wedding Announcement (W2)
4521.14 Sorin the Mirthless (BB2)
4549.36 Henrika Domnathi (BB2)

Score: 62.3747
Iteration: 86
Lands { W=8 B=8 C=1 }
1403.4 Traveling Minister (W)
1525.06 Wedding Invitation (2)
1650.48 Parish-Blade Trainee (W1)
1746.38 Edgar's Awakening (BB3)
1824.21 Catapult Fodder (B2)
1824.21 Catapult Fodder (B2)
2039.03 Distracting Geist (W2)
2332.08 Heron of Hope (W3)
2856.5 Markov Purifier (WB1)
2857.92 Rot-Tide Gargantua (BB3)
2891.54 Savior of Ollenbock (WW1)
2904.69 Voldaren Bloodcaster (B1)
3004.72 Katilda, Dawnhart Martyr (WW1)
3197.19 Fell Stinger (B2)
3362.07 Angelic Quartermaster (WW3)
3399.51 Diregraf Scavenger (B3)
3399.51 Diregraf Scavenger (B3)
3663.3 Bleed Dry (BB2)
3701.85 Gryffwing Cavalry (W3)
3968.19 Sorin the Mirthless (BB2)
4162.95 Wedding Announcement (W2)
4382.74 Henrika Domnathi (BB2)
4519.15 By Invitation Only (WW3)
*/

/* R2
Score: 134.28
Iteration: 52
Param experiment:   B=11  R=6
904.638 Flame-Blessed Bolt
1237.65 Ceremonial Knife
1450.93 Gift of Fangs
1741.08 Abrade
2234.77 Blood Petal Celebrant
2308.31 Weary Prisoner
2344.96 Gluttonous Guest
2382.53 Restless Bloodseeker
2461.48 Doomed Dissenter
2904.57 Catapult Fodder
2904.57 Catapult Fodder
2904.6 Bleed Dry
3014.41 Wedding Security
3490.32 Diregraf Scavenger
3490.32 Diregraf Scavenger
3503.35 Voldaren Bloodcaster
3513.87 Rot-Tide Gargantua
3572.5 Alluring Suitor
3572.5 Alluring Suitor
4107.08 Falkenrath Celebrants
4514.42 Fell Stinger
4604.87 Creepy Puppeteer
5349.43 Sorin the Mirthless

*/
