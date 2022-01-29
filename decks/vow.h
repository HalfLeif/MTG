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
    "Sorin the Mirthless",      //
    "Henrika Domnathi",         //
    "Katilda, Dawnhart Martyr", //
    "Bleed Dry",                //
    "By Invitation Only",       //
    "Sigarda's Imprisonment",
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
Score: 147.909
Iteration: 55
Param experiment:   B=9  W=8
1338.08 Groom's Finery
1633.66 Gift of Fangs
1758.99 Gryff Rider
1893.76 Sigarda's Imprisonment
1964.72 Parish-Blade Trainee
2491.65 Catapult Fodder
2524.6 Heron of Hope
2541.56 Doomed Dissenter
2892.97 Rot-Tide Gargantua
2998.94 Savior of Ollenbock
3080.07 Markov Purifier
3268.84 Voldaren Bloodcaster
3469.26 Katilda, Dawnhart Martyr
3497.34 Diregraf Scavenger
3497.34 Diregraf Scavenger
3922.46 Fell Stinger
3931.43 Angelic Quartermaster
3935.54 Bleed Dry
4303.22 Gryffwing Cavalry
4941.02 Sorin the Mirthless
4987.02 By Invitation Only
5322.96 Henrika Domnathi
5549.86 Wedding Announcement
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
