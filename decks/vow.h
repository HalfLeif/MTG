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

    // Round 4
    "Lantern of the Lost",
    "Hullbreaker Horror",
    "Vampire's Vengeance",
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

constexpr std::string_view kVowDeck[] = {
    "Restless Bloodseeker",
    "Traveling Minister",
    "Courier Bat",
    "Doomed Dissenter",
    "Catapult Fodder",
    "Path of Peril",
    "Wedding Security",
    "Markov Purifier",
    "Voldaren Bloodcaster",
    "Savior of Ollenbock",
    "Katilda, Dawnhart Martyr",
    "Rot-Tide Gargantua",
    "Diregraf Scavenger",
    "Diregraf Scavenger",
    "Fell Stinger",
    "Gryffwing Cavalry",
    "By Invitation Only",
    "Angelic Quartermaster",
    "Bleed Dry",
    "Sorin the Mirthless",
    "Wedding Announcement",
    "Henrika Domnathi",
};

std::vector<std::string_view> VowDeck() {
  return std::vector<std::string_view>(std::begin(kVowDeck),
                                       std::end(kVowDeck));
}

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
