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

Score: 132.177
Iteration: 59
Param experiment:   B=9  R=8
663.223 Dread Fugue
1262.37 Ceremonial Knife
1584.61 Wedding Invitation
1983.14 Sanguine Statuette
2111.93 Restless Bloodseeker
2185.23 Unhallowed Phalanx
2189.35 Doomed Dissenter
2370.1 Courier Bat
2527.04 Weary Prisoner
2527.04 Weary Prisoner
2535.92 Blood Petal Celebrant
2812.34 Catapult Fodder
2812.34 Catapult Fodder
2820.33 Wedding Security
3490.54 Rot-Tide Gargantua
3543.29 Voldaren Bloodcaster
3853.42 Diregraf Scavenger
3964.32 Alluring Suitor
3964.32 Alluring Suitor
4087.96 Falkenrath Celebrants
4481.97 Fell Stinger
4876.91 Creepy Puppeteer
4932.59 Sorin the Mirthless

Score: 131.249
Iteration: 30
Param experiment:   B=9  U=8
1422.51 Steelclad Spirit
1497.92 Gift of Fangs
1638.58 Honored Heirloom
1693.69 Scattered Thoughts
1899.4 Courier Bat
1966.06 Skulking Killer
2016.04 Unhallowed Phalanx
2016.55 Mischievous Catgeist
2316.41 Restless Bloodseeker
2385.2 Doomed Dissenter
2608.13 Stitched Assistant
3081.79 Catapult Fodder
3081.79 Catapult Fodder
3105.22 Voldaren Bloodcaster
3296.93 Wedding Security
3472.19 Binding Geist
3524.12 Diregraf Scavenger
3656.23 Overcharged Amalgam
3765.23 Rot-Tide Gargantua
3924.97 Whispering Wizard
4813.7 Fell Stinger
4958.32 Sorin the Mirthless
5133.29 Mirrorhall Mimic

Score: 129.698
Iteration: 43
Param experiment:   B=11  R=6
1067.51 Vampire's Kiss
1449.38 Gift of Fangs
1508.22 Blood Servitor
1552.45 Edgar's Awakening
1813.22 Wedding Invitation
1966.06 Skulking Killer
2285.22 Doomed Dissenter
2335.4 Courier Bat
2408.98 Restless Bloodseeker
2610.81 Weary Prisoner
2610.81 Weary Prisoner
2797.11 Catapult Fodder
2797.11 Catapult Fodder
2869.46 Wedding Security
3321.13 Voldaren Bloodcaster
3516.53 Alluring Suitor
3516.53 Alluring Suitor
3788.55 Rot-Tide Gargantua
3864.32 Diregraf Scavenger
4030.62 Falkenrath Celebrants
4433.29 Fell Stinger
4735.94 Creepy Puppeteer
5303.11 Sorin the Mirthless

*/
