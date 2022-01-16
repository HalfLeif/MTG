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
};

std::vector<std::string_view> VowCards() {
  return std::vector<std::string_view>(std::begin(kVowCards),
                                       std::end(kVowCards));
}

/*
Found the best generated decks!

Score: 131.281
Iteration: 56
Param experiment:   B=9  U=8
1368.83 Gift of Fangs
1466.91 Steelclad Spirit
1466.91 Steelclad Spirit
1466.91 Steelclad Spirit
1961.25 Courier Bat
2007.88 Unhallowed Phalanx
2073.05 Skulking Killer
2274.46 Mischievous Catgeist
2294.84 Stitched Assistant
2484.69 Runo Stromkirk
2550.12 Doomed Dissenter
2921.05 Wedding Security
3214.91 Catapult Fodder
3214.91 Catapult Fodder
3325.67 Diregraf Scavenger
3368.56 Voldaren Bloodcaster
3454.26 Rot-Tide Gargantua
3455.95 Binding Geist
4011.78 Whispering Wizard
4046.39 Overcharged Amalgam
4528.85 Fell Stinger
4978.9 Sorin the Mirthless
5266.29 Mirrorhall Mimic

Score: 130.426
Iteration: 59
Param experiment:   B=11  U=6
1218.57 Ceremonial Knife
1291.25 Lantern Bearer
1603.19 Blood Servitor
1771.49 Wedding Invitation
1786.29 Chill of the Grave
1892.42 Honored Heirloom
2168.92 Unhallowed Phalanx
2249.4 Courier Bat
2348.4 Skulking Killer
2394.74 Restless Bloodseeker
2634.65 Doomed Dissenter
2927.44 Overcharged Amalgam
3046.35 Wedding Security
3167.62 Voldaren Bloodcaster
3246.45 Binding Geist
3295.1 Catapult Fodder
3295.1 Catapult Fodder
3701.08 Whispering Wizard
3753.1 Diregraf Scavenger
3892.2 Rot-Tide Gargantua
4566.71 Fell Stinger
4959.37 Mirrorhall Mimic
5411.18 Sorin the Mirthless

Score: 127.236
Iteration: 62
Param experiment:   B=7  W=6  U=4
1043.25 Radiant Grace
1535.55 Stitched Assistant
1681.61 Groom's Finery
1768.88 Gryff Rider
2108.88 Restless Bloodseeker
2183.54 Skulking Killer
2184.33 Binding Geist
2328.51 Doomed Dissenter
2563.75 Catapult Fodder
2563.75 Catapult Fodder
2775.81 Heron-Blessed Geist
2830.6 Katilda, Dawnhart Martyr
2857.18 Wedding Security
3161.97 Distracting Geist
3288.68 Voldaren Bloodcaster
3322.11 Rot-Tide Gargantua
3408.65 Whispering Wizard
3456.52 Diregraf Scavenger
3771.87 Gryffwing Cavalry
3984.88 Mirrorhall Mimic
3998.8 Fell Stinger
4114.35 Sorin the Mirthless
4550.35 Wedding Announcement
*/
