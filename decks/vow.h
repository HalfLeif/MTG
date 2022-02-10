#pragma once

#include <string_view>

constexpr std::string_view kVowCards[] = {
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
};

constexpr std::string_view kVowForcedCards[] = {
    "Traveling Minister",
};

std::vector<std::string_view> VowCards() {
  return std::vector<std::string_view>(std::begin(kVowCards),
                                       std::end(kVowCards));
}

std::vector<std::string_view> VowForcedCards() {
  return std::vector<std::string_view>(std::begin(kVowForcedCards),
                                       std::end(kVowForcedCards));
}

/* R3
Score: 62.1599
Iteration: 110
Lands { W=8 B=9 C=1 }
587.845 Sanctify (W1) -> Restless Bloodseeker (B1)
672.862 Traveling Minister (W)
901.606 Courier Bat (B2)
967.654 Doomed Dissenter (B1)
1046.53 Catapult Fodder (B2)
1156.39 Path of Peril (BB1)
1376.83 Wedding Security (BB3)
1385.33 Markov Purifier (WB1)
1418.34 Voldaren Bloodcaster (B1)
1420.98 Savior of Ollenbock (WW1)
1452.74 Katilda, Dawnhart Martyr (WW1)
1534.11 Rot-Tide Gargantua (BB3)
1537.29 Diregraf Scavenger (B3)
1537.29 Diregraf Scavenger (B3)
1724.51 Fell Stinger (B2)
1900.22 Gryffwing Cavalry (W3)
1900.51 By Invitation Only (WW3)
2010.25 Angelic Quartermaster (WW3)
2027.24 Bleed Dry (BB2)
2137.86 Sorin the Mirthless (BB2)
2215.09 Wedding Announcement (W2)
2538 Henrika Domnathi (BB2)

Score: 61.8128
Iteration: 79
Lands { W=7 B=10 C=1 }
656.137 Bride's Gown (W1)
718.52 Traveling Minister (W)
765.443 Boarded Window (3)
915.501 Courier Bat (B2)
921.588 Sigarda's Imprisonment (W2)
1043.53 Heron of Hope (W3)
1227.92 Path of Peril (BB1)
1280.9 Voldaren Bloodcaster (B1)
1307.39 Savior of Ollenbock (WW1)
1401.63 Wedding Security (BB3)
1415.27 Markov Purifier (WB1)
1561.07 Rot-Tide Gargantua (BB3)
1657.25 Diregraf Scavenger (B3)
1657.25 Diregraf Scavenger (B3)
1694.29 Fell Stinger (B2)
1769.59 Gryffwing Cavalry (W3)
1816.22 Angelic Quartermaster (WW3)
2040.46 Bleed Dry (BB2)
2131.17 Wedding Announcement (W2)
2208.8 By Invitation Only (WW3)
2270.92 Sorin the Mirthless (BB2)
2713.55 Henrika Domnathi (BB2)

Score: 61.7571
Iteration: 92
Lands { W=8 B=8 C=1 }
564.134 Honored Heirloom (3)
662.048 Traveling Minister (W)
807.092 Edgar's Awakening (BB3)
908.349 Restless Bloodseeker (B1)
976.208 Doomed Dissenter (B1)
1046.53 Catapult Fodder (B2)
1046.53 Catapult Fodder (B2)
1065.41 Heron of Hope (W3)
1163.48 Wedding Security (BB3)
1259.64 Voldaren Bloodcaster (B1)
1393.07 Distracting Geist (W2)
1552.98 Rot-Tide Gargantua (BB3)
1590.93 Markov Purifier (WB1)
1592.03 Diregraf Scavenger (B3)
1592.03 Diregraf Scavenger (B3)
1739.88 Angelic Quartermaster (WW3)
1811.49 Gryffwing Cavalry (W3)
1864.24 By Invitation Only (WW3)
1887.16 Bleed Dry (BB2)
1948.13 Fell Stinger (B2)
1990.01 Sorin the Mirthless (BB2)
2175.01 Henrika Domnathi (BB2)
2290.17 Wedding Announcement (W2)

Score: 61.4621
Iteration: 119
Lands { W=6 B=9 C=1 }
467.908 Sigarda's Imprisonment (W2)
585.149 Traveling Minister (W)
777.282 Distracting Geist (W2)
847.229 Catapult Fodder (B2)
847.229 Catapult Fodder (B2)
919.096 Savior of Ollenbock (WW1)
980.086 Heron of Hope (W3)
1101.31 Doomed Dissenter (B1)
1123.34 Katilda, Dawnhart Martyr (WW1)
1174.27 Path of Peril (BB1)
1178.37 Wedding Security (BB3)
1245.48 Voldaren Bloodcaster (B1)
1373.35 Markov Purifier (WB1)
1392.88 Diregraf Scavenger (B3)
1392.88 Diregraf Scavenger (B3)
1421.8 Angelic Quartermaster (WW3)
1582.28 Gryffwing Cavalry (W3)
1652.74 Rot-Tide Gargantua (BB3)
1769.94 By Invitation Only (WW3)
1817.18 Fell Stinger (B2)
2005.28 Wedding Announcement (W2)
2037.81 Bleed Dry (BB2)
2421.72 Sorin the Mirthless (BB2)
2606.44 Henrika Domnathi (BB2)
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
