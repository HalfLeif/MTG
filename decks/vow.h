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

// Found the best generated decks!
//
// Score: 131.624
// Iteration: 61
// Param experiment:   B=9  R=8
// 1199.92 Ceremonial Knife
// 1412.55 Persistent Specimen
// 1608.99 Edgar's Awakening
// 1677.91 Blood Servitor
// 1742.65 Honored Heirloom
// 1793.69 Sanguine Statuette
// 2000.03 Restless Bloodseeker
// 2062.57 Doomed Dissenter
// 2448.55 Courier Bat
// 2488.15 Blood Petal Celebrant
// 2776.11 Wedding Security
// 2989.63 Weary Prisoner
// 3093.98 Voldaren Bloodcaster
// 3578.65 Rot-Tide Gargantua
// 3890.49 Diregraf Scavenger
// 4096.15 Falkenrath Celebrants
// 4510.82 Fell Stinger
// 4917.15 Sorin the Mirthless
// 4998.09 Creepy Puppeteer
// 5974.33 Catapult Fodder
// 7855.78 Alluring Suitor
//
// Score: 129.987
// Iteration: 47
// Param experiment:   B=11  R=6
// 1253.69 Ceremonial Knife
// 1517.82 Kessig Flamebreather
// 1644.58 Wedding Invitation
// 1703 Sanguine Statuette
// 1783.32 Edgar's Awakening
// 2106.84 Restless Bloodseeker
// 2109.3 Lightning Wolf
// 2128.15 Unhallowed Phalanx
// 2269.02 Courier Bat
// 2488.88 Weary Prisoner
// 2676.91 Doomed Dissenter
// 2972.64 Wedding Security
// 3538.3 Voldaren Bloodcaster
// 3607.15 Rot-Tide Gargantua
// 3809.42 Falkenrath Celebrants
// 3914.48 Diregraf Scavenger
// 4523.44 Fell Stinger
// 4664.22 Creepy Puppeteer
// 5424.05 Sorin the Mirthless
// 5661.58 Catapult Fodder
// 6748.75 Alluring Suitor
//
// Score: 129.415
// Iteration: 53
// Param experiment:   B=11  U=6
// 1632.23 Honored Heirloom
// 1637.1 Scattered Thoughts
// 1759.66 Mischievous Catgeist
// 1967.75 Skywarp Skaab
// 2094.01 Courier Bat
// 2265.97 Skulking Killer
// 2366.86 Steelclad Spirit
// 2382.81 Stitched Assistant
// 2439.5 Restless Bloodseeker
// 2590.32 Doomed Dissenter
// 3116.38 Overcharged Amalgam
// 3208.49 Wedding Security
// 3300.05 Binding Geist
// 3568.28 Rot-Tide Gargantua
// 3593.91 Diregraf Scavenger
// 3628.16 Voldaren Bloodcaster
// 3714.78 Whispering Wizard
// 4593.75 Fell Stinger
// 4926.12 Mirrorhall Mimic
// 5457.5 Sorin the Mirthless
// 6356.04 Catapult Fodder
