#pragma once

#include <string_view>
#include <vector>

#include "../core/sealed_deck.h"

class Snc : public SealedDeck {
public:
  std::string_view data_path() const override { return "data/snc/cards.csv"; }

  // Minimum number of colors in generated deck.
  int MinColors() const override { return 2; }

  // Maximum number of colors in generated deck.
  int MaxColors() const override { return 3; }

  std::vector<std::string_view> cards() const override {
    return {
        "Goldhound", "Chrome Cat", "Witness Protection",
        "Fake Your Own Death", // Nice combat trick
        "Sky Crier",           // Cheap flyer (W)
        "Antagonize",          // Comat trick
        "For the Family",      // Nice combat trick
        "Speakeasy Server", "Mayhem Patrol", "Rhox Pummeler",
        "Fatal Grudge", // Kind of removal
        "Illicit Shipment", "Sizzling Soloist", "Riveteers Ascendancy",
        // p2
        "Backstreet Bruiser",
        "Deal Gone Bad",   // Removal
        "Hold for Ransom", // Nice removal (W)
        "Broken Wings",    // Removal (G)
        "Wrecking Crew", "Civic Gardener",
        "Masked Bandits",           // Good creature + mana fix
        "Inspiring Overseer",       // Cheap flyer (W)
        "Illuminator Virtuoso",     // Combo
        "Ceremonial Groundbreaker", // Nice Equipment (WG)
        "Public Enemy",
        "Park Heights Pegasus", // Cheap flyer (WG)
        "Rogues' Gallery",
        // p3
        "Expendable Lackey", // Can't be blocked (B)
        "Fake Your Own Death", "Backup Agent", "Ready to Rumble", "Halo Scarab",
        "Capenna Express",
        "Strangle", // Cheap removal (R)
        "Girder Goons",
        "Cabaretti Initiate", // Double strike with (G+R/W)
        "Elegant Entourage",
        "Out of the Way", // Kind of removal
        "Riveteers Requisitioner", "Evolving Door",
        // p4
        "Case the Joint", "Dig Up the Body",
        "Revelation of Power", // Combat trick (W)
        "Jackhammer", "Gilded Pinions", "Snooping Newsie", "Body Dropper",
        "High-Rise Sawjack", "Rumor Gatherer", "Hypnotic Grifter",
        "Suspicious Bookcase",     // Can't be blocked
        "Soul of Emancipation",    // Great first pick (GWU)
        "Jaxis, the Troublemaker", // Great first pick (R)
        // p5
        "Quick-Draw Dagger",      // Combat trick
        "Majestic Metamorphosis", // Combat trick
        "Corrupt Court Official", "Sky Crier", "Sticky Fingers",
        "Light 'Em Up", // Cheap removal (R)
        "Attended Socialite",
        "Murder",         // Great removal (BB)
        "Jetmir's Fixer", // Boostable (GR)
        "Rumor Gatherer", "Venom Connoisseur",
        "Knockout Blow", // Removal
        "Tenacious Underdog",
        // p6
        "Case the Joint",
        "Incriminate",      // Removal (B)
        "Celebrity Fencer", // Nice creature (W)
        "Sticky Fingers", "Quick-Draw Dagger",
        "Jewel Thief", // Nice creature (G)
        "Join the Maestros", "Pugnacious Pugilist", "Rocco, Cabaretti Caterer",
        "Freelance Muscle",    // Nice creature (G)
        "Giada, Font of Hope", // Cheap flyer (W)
    };
  }

  std::vector<std::string_view> forced_cards() const override {
    return {
        "Freelance Muscle",
        "Hold for Ransom",
        "Knockout Blow",
    };
  }

  std::vector<std::string_view> chosen_deck() const override { return {}; }
};

/*

Score: 56.3662
Iteration: 124
Lands { W=5 R=7 G=6 }
1317.01 Strangle (R)
1362.46 Halo Scarab (2)
1625.68 Celebrity Fencer (W3)
1644.68 Illuminator Virtuoso (W1)
1713.48 Light 'Em Up (R1)
1910.06 Quick-Draw Dagger (3)
1910.06 Quick-Draw Dagger (3)
2069.65 Mayhem Patrol (R1)
2249.53 Riveteers Requisitioner (R1)
2375.38 Giada, Font of Hope (W1)
2455.59 Wrecking Crew (R4)
2494.24 Sizzling Soloist (R3)
2588.2 High-Rise Sawjack (G2)
2615.55 Rhox Pummeler (G5)
2916.14 Knockout Blow (W2)
3114.57 Pugnacious Pugilist (RR3)
3629.44 Jewel Thief (G2)
3669.63 Inspiring Overseer (W2)
3741.28 Freelance Muscle (G4)
3999.66 Elegant Entourage (G3)
4173.47 Rocco, Cabaretti Caterer (WRG2)
5071.42 Jaxis, the Troublemaker (R3)

Score: 56.1068
Iteration: 116
Lands { W=6 R=5 G=6 }
1136.71 Halo Scarab (2)
1376.38 Sky Crier (W1)
1376.38 Sky Crier (W1)
1500.88 Backup Agent (W1)
1887.81 Quick-Draw Dagger (3)
1887.81 Quick-Draw Dagger (3)
1905.77 Ready to Rumble (R4)
1911.11 Riveteers Requisitioner (R1)
2058.64 Ceremonial Groundbreaker (WG1)
2084.44 Capenna Express (G3)
2126.38 Illuminator Virtuoso (W1)
2218.2 Pugnacious Pugilist (RR3)
2251.1 Wrecking Crew (R4)
2333 Sizzling Soloist (R3)
2335.58 High-Rise Sawjack (G2)
2531.45 Giada, Font of Hope (W1)
3197.6 Knockout Blow (W2)
3530.99 Jewel Thief (G2)
3670.29 Freelance Muscle (G4)
3879.69 Inspiring Overseer (W2)
3905.18 Elegant Entourage (G3)
4063.15 Rocco, Cabaretti Caterer (WRG2)
4701.28 Jaxis, the Troublemaker (R3)

Score: 55.2223
Iteration: 85
Lands { W=6 R=5 G=5 }
1122.32 Hold for Ransom (W1)
1402.67 Sky Crier (W1)
1589.29 Park Heights Pegasus (WG)
1618.49 Quick-Draw Dagger (3)
1618.49 Quick-Draw Dagger (3)
1636.07 Mayhem Patrol (R1)
1729.06 Rumor Gatherer (WW1)
1730.46 Celebrity Fencer (W3)
1797.36 Riveteers Requisitioner (R1)
1902.09 Illuminator Virtuoso (W1)
1992.18 Ready to Rumble (R4)
2030.73 Pugnacious Pugilist (RR3)
2037.01 High-Rise Sawjack (G2)
2131.23 Capenna Express (G3)
2193.18 Ceremonial Groundbreaker (WG1)
2344.5 Sizzling Soloist (R3)
2750.95 Giada, Font of Hope (W1)
3054.71 Jewel Thief (G2)
3137.72 Freelance Muscle (G4)
3255.33 Knockout Blow (W2)
3484.06 Rocco, Cabaretti Caterer (WRG2)
3737.99 Elegant Entourage (G3)
3994.92 Inspiring Overseer (W2)
4332.54 Jaxis, the Troublemaker (R3)

Score: 55.0937
Iteration: 114
Lands { B=6 R=6 G=6 }
1383.08 Fake Your Own Death (B1)
1563.12 Light 'Em Up (R1)
1748.62 Mayhem Patrol (R1)
1799.7 Quick-Draw Dagger (3)
1799.7 Quick-Draw Dagger (3)
1827.16 Join the Maestros (B4)
2140.05 Corrupt Court Official (B1)
2300.62 Riveteers Requisitioner (R1)
2307.76 Deal Gone Bad (B3)
2326.83 Dig Up the Body (B2)
2355.72 Sizzling Soloist (R3)
2394.29 Murder (BB1)
2486.46 Wrecking Crew (R4)
2515.01 High-Rise Sawjack (G2)
2793.13 Tenacious Underdog (B1)
3130.14 Girder Goons (B4)
3144.13 Pugnacious Pugilist (RR3)
3169.86 Rogues' Gallery (B2)
3264.1 Jewel Thief (G2)
3873.17 Elegant Entourage (G3)
4035.48 Freelance Muscle (G4)
4679.07 Jaxis, the Troublemaker (R3)

Score: 55.027
Iteration: 116
Lands { W=9 G=8 }
1114.1 For the Family (G)
1172.49 Broken Wings (G2)
1513.5 Sky Crier (W1)
1513.5 Sky Crier (W1)
1626.29 Quick-Draw Dagger (3)
1626.29 Quick-Draw Dagger (3)
1814.52 Backup Agent (W1)
2234.98 Speakeasy Server (W4)
2277.53 Park Heights Pegasus (WG)
2318.77 Rhox Pummeler (G5)
2328.91 Celebrity Fencer (W3)
2334.75 Rumor Gatherer (WW1)
2334.75 Rumor Gatherer (WW1)
2505.66 High-Rise Sawjack (G2)
2524.22 Illuminator Virtuoso (W1)
2608.85 Capenna Express (G3)
2796.68 Ceremonial Groundbreaker (WG1)
3071.53 Giada, Font of Hope (W1)
3597.76 Knockout Blow (W2)
3772.51 Freelance Muscle (G4)
3910.13 Jewel Thief (G2)
4331.22 Elegant Entourage (G3)
4370.02 Inspiring Overseer (W2)

Score: 54.9073
Iteration: 115
Lands { W=5 R=6 G=7 }
1273.53 Suspicious Bookcase (2)
1367.82 Venom Connoisseur (G1)
1421.52 Park Heights Pegasus (WG)
1523.6 Backup Agent (W1)
1829.86 Illuminator Virtuoso (W1)
1872.08 Quick-Draw Dagger (3)
1900.58 Mayhem Patrol (R1)
2192.13 Rhox Pummeler (G5)
2230.6 Riveteers Requisitioner (R1)
2241.12 Ceremonial Groundbreaker (WG1)
2362.86 Giada, Font of Hope (W1)
2402.72 Capenna Express (G3)
2502.55 Sizzling Soloist (R3)
2503.93 High-Rise Sawjack (G2)
2539.8 Wrecking Crew (R4)
2904.61 Knockout Blow (W2)
3547.2 Inspiring Overseer (W2)
3799.39 Freelance Muscle (G4)
3804.74 Jewel Thief (G2)
4131.98 Rocco, Cabaretti Caterer (WRG2)
4221.68 Elegant Entourage (G3)
4901.98 Jaxis, the Troublemaker (R3)

*/
