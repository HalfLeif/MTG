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

// Recently algorithm suggests 19-20 lands, which is unexpected.
// 16-18 is considered normal. Not sure where the discrepancy comes from.

/* R3
Score: 150.265
Iteration: 80
Lands { W=8 B=10 C=1 }
1685.16 Traveling Minister
1780.38 Pointed Discussion
2352.07 Restless Bloodseeker
2436.78 Doomed Dissenter
2632.1 Wedding Security
2635.3 Distracting Geist
2873.09 Path of Peril
3184.2 Katilda, Dawnhart Martyr
3317.99 Diregraf Scavenger
3317.99 Diregraf Scavenger
3553.15 Markov Purifier
3831.36 Voldaren Bloodcaster
3866.28 Rot-Tide Gargantua
4287.68 Angelic Quartermaster
4321.43 Bleed Dry
4391.94 Gryffwing Cavalry
4460.36 Fell Stinger
4776.66 By Invitation Only
5094.92 Wedding Announcement
5916.8 Sorin the Mirthless
6322.69 Henrika Domnathi

Score: 148.885
Iteration: 76
Lands { W=8 B=8 C=1 }
1379.52 Gift of Fangs
1548.7 Sanctify
1566.25 Vampire's Kiss
1739.83 Traveling Minister
1985.45 Sigarda's Imprisonment
2374.45 Gluttonous Guest
2418.09 Path of Peril
2447.41 Restless Bloodseeker
2798.06 Heron of Hope
2990.24 Markov Purifier
3230.26 Savior of Ollenbock
3403.45 Voldaren Bloodcaster
3565.87 Fell Stinger
3679.02 Diregraf Scavenger
3679.02 Diregraf Scavenger
3864.12 Katilda, Dawnhart Martyr
4033.34 Bleed Dry
4065.02 Angelic Quartermaster
4594.04 Gryffwing Cavalry
4796.13 Sorin the Mirthless
4979.77 By Invitation Only
5264.97 Wedding Announcement
5483.63 Henrika Domnathi

Score: 148.854
Iteration: 119
Lands { W=8 B=10 C=1 }
1703.18 Traveling Minister
1957.6 Courier Bat
2359.35 Catapult Fodder
2528.03 Savior of Ollenbock
2752.43 Distracting Geist
2765.03 Doomed Dissenter
3034.28 Katilda, Dawnhart Martyr
3056.31 Wedding Security
3169.89 Markov Purifier
3312.17 Diregraf Scavenger
3312.17 Diregraf Scavenger
3389.07 Rot-Tide Gargantua
3829.65 Angelic Quartermaster
3858.28 Voldaren Bloodcaster
4184.36 Fell Stinger
4327.86 Gryffwing Cavalry
4972.51 By Invitation Only
5079.99 Bleed Dry
5156.76 Wedding Announcement
5496.92 Sorin the Mirthless
6248.31 Henrika Domnathi
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
