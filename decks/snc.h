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
        "Freelance Muscle", "Jaxis, the Troublemaker", "Strangle",
        // "Knockout Blow",
    };
  }

  std::vector<std::string_view> chosen_deck() const override {
    return {
        "Strangle",
        "For the Family",
        "Suspicious Bookcase",
        // Forest <- "Illuminator Virtuoso",
        "Sky Crier",            // <- "Hold for Ransom",
        "Park Heights Pegasus", // <- "Sky Crier",
        "Mayhem Patrol",
        "Riveteers Requisitioner",
        "Giada, Font of Hope",
        "Antagonize",
        "Jewel Thief",
        "Inspiring Overseer",
        "Quick-Draw Dagger",
        "Knockout Blow",
        "High-Rise Sawjack", // <- "Celebrity Fencer",
        "Sizzling Soloist",
        "Elegant Entourage",
        "Jaxis, the Troublemaker",
        "Ready to Rumble",
        "Wrecking Crew", // <- "Rhox Pummeler",
        "Pugnacious Pugilist",
        "Freelance Muscle",
        "Rocco, Cabaretti Caterer",
    };
  }
};

/*


Score: 56.3221
Iteration: 70
Lands { W=6 R=7 G=5 }
1120.4 Jetmir's Fixer (RG)
1199.3 Strangle (R)
1275.58 Halo Scarab (2)
1641.32 Sky Crier (W1)
1889.09 Light 'Em Up (R1)
2028.09 Celebrity Fencer (W3)
2039.01 Quick-Draw Dagger (3)
2124.44 Ready to Rumble (R4)
2298.23 Mayhem Patrol (R1)
2456.05 Riveteers Requisitioner (R1)
2484.66 High-Rise Sawjack (G2)
2649.83 Sizzling Soloist (R3)
2655.6 Giada, Font of Hope (W1)
2709.28 Wrecking Crew (R4)
3073.88 Jewel Thief (G2)
3192.86 Knockout Blow (W2)
3514.47 Pugnacious Pugilist (RR3)
3565.05 Rocco, Cabaretti Caterer (WRG3)
3819.54 Elegant Entourage (G3)
4000.88 Freelance Muscle (G4)
4097.78 Inspiring Overseer (W2)
4835.76 Jaxis, the Troublemaker (R3)

Score: 56.0942
Iteration: 89
Lands { W=5 R=7 G=6 }
1352.4 Strangle (R)
1353.74 Civic Gardener (G1)
1432.1 Jetmir's Fixer (RG)
1855.98 Illuminator Virtuoso (W1)
1920.42 Light 'Em Up (R1)
2021.96 Mayhem Patrol (R1)
2091.23 Quick-Draw Dagger (3)
2202.06 Rhox Pummeler (G5)
2242.37 Ceremonial Groundbreaker (WG1)
2271.78 Ready to Rumble (R4)
2287 Riveteers Requisitioner (R1)
2379.66 Sizzling Soloist (R3)
2513.17 Giada, Font of Hope (W1)
2578.22 High-Rise Sawjack (G2)
3077.23 Knockout Blow (W2)
3429.22 Jewel Thief (G2)
3454.36 Rocco, Cabaretti Caterer (WRG3)
3651.24 Elegant Entourage (G3)
3657.62 Pugnacious Pugilist (RR3)
3765.09 Inspiring Overseer (W2)
4012.53 Freelance Muscle (G4)
4834.79 Jaxis, the Troublemaker (R3)

Score: 56.0502
Iteration: 114
Lands { B=6 R=7 G=5 }
1326.34 Strangle (R)
1412.4 Halo Scarab (2)
1568.98 Suspicious Bookcase (2)
1954.92 Mayhem Patrol (R1)
2100.39 Quick-Draw Dagger (3)
2164.83 Murder (BB1)
2168.68 Riveteers Requisitioner (R1)
2174.63 Deal Gone Bad (B3)
2244.2 Masked Bandits (BRG3)
2297.88 Corrupt Court Official (B1)
2338.59 Dig Up the Body (B2)
2413.38 Wrecking Crew (R4)
2464.44 High-Rise Sawjack (G2)
2488.97 Sizzling Soloist (R3)
2819.45 Tenacious Underdog (B1)
3023.5 Jewel Thief (G2)
3449.55 Rogues' Gallery (B2)
3474.66 Pugnacious Pugilist (RR3)
3591.31 Girder Goons (B4)
3715.49 Elegant Entourage (G3)
3945.09 Freelance Muscle (G4)
5136.96 Jaxis, the Troublemaker (R3)

Score: 55.8581
Iteration: 135
Lands { W=5 R=7 G=6 }
1226.81 Sky Crier (W1)
1266.64 Venom Connoisseur (G1)
1359.61 Strangle (R)
1493.1 Backup Agent (W1)
1769.28 Illuminator Virtuoso (W1)
2121.52 Quick-Draw Dagger (3)
2121.52 Quick-Draw Dagger (3)
2164.7 Mayhem Patrol (R1)
2289.87 Ready to Rumble (R4)
2511.96 Sizzling Soloist (R3)
2520.15 Riveteers Requisitioner (R1)
2530.23 High-Rise Sawjack (G2)
2631.79 Knockout Blow (W2)
2649.3 Wrecking Crew (R4)
2679.75 Giada, Font of Hope (W1)
3056.8 Inspiring Overseer (W2)
3250.85 Rocco, Cabaretti Caterer (WRG3)
3389.87 Pugnacious Pugilist (RR3)
3624.5 Jewel Thief (G2)
4030.07 Elegant Entourage (G3)
4142.99 Freelance Muscle (G4)
5467.28 Jaxis, the Troublemaker (R3)

Score: 55.7486
Iteration: 62
Lands { B=7 R=5 G=6 }
1073.01 Strangle (R)
1573.48 Suspicious Bookcase (2)
1615.6 Quick-Draw Dagger (3)
1615.6 Quick-Draw Dagger (3)
1701.07 Riveteers Requisitioner (R1)
1763.42 Mayhem Patrol (R1)
1953.29 Capenna Express (G3)
2083.08 Pugnacious Pugilist (RR3)
2145.29 Dig Up the Body (B2)
2246.12 Sizzling Soloist (R3)
2277.16 Deal Gone Bad (B3)
2329.65 Corrupt Court Official (B1)
2341.38 Rhox Pummeler (G5)
2632.77 High-Rise Sawjack (G2)
2783.46 Murder (BB1)
2903.03 Tenacious Underdog (B1)
3618.92 Girder Goons (B4)
3723.55 Rogues' Gallery (B2)
3751.22 Jewel Thief (G2)
4332.61 Elegant Entourage (G3)
4340.98 Freelance Muscle (G4)
4937.45 Jaxis, the Troublemaker (R3)

Score: 55.433
Iteration: 130
Lands { B=6 R=7 G=5 }
1345.4 Fake Your Own Death (B1)
1372.19 Strangle (R)
1676.93 Light 'Em Up (R1)
2057 Murder (BB1)
2081.5 Mayhem Patrol (R1)
2100.94 Quick-Draw Dagger (3)
2100.94 Quick-Draw Dagger (3)
2141.03 Ready to Rumble (R4)
2223.87 Riveteers Requisitioner (R1)
2333.16 Rhox Pummeler (G5)
2379.15 Wrecking Crew (R4)
2492.58 Corrupt Court Official (B1)
2521.02 Sizzling Soloist (R3)
2572.12 High-Rise Sawjack (G2)
2665.27 Tenacious Underdog (B1)
2938.5 Rogues' Gallery (B2)
3183.34 Jewel Thief (G2)
3252.33 Elegant Entourage (G3)
3487.79 Girder Goons (B4)
3713.58 Pugnacious Pugilist (RR3)
3911.96 Freelance Muscle (G4)
4831.88 Jaxis, the Troublemaker (R3)

Score: 55.3661
Iteration: 89
Lands { W=6 R=6 G=6 }
1277.59 Strangle (R)
1291.05 Jetmir's Fixer (RG)
1330.75 Civic Gardener (G1)
1818.67 Light 'Em Up (R1)
1922.32 Mayhem Patrol (R1)
2143.23 Rhox Pummeler (G5)
2166.08 Quick-Draw Dagger (3)
2174.73 Illuminator Virtuoso (W1)
2378.08 Ceremonial Groundbreaker (WG1)
2460.03 Riveteers Requisitioner (R1)
2522.93 High-Rise Sawjack (G2)
2579.84 Ready to Rumble (R4)
2582.38 Sizzling Soloist (R3)
2592.98 Pugnacious Pugilist (RR3)
2664.82 Giada, Font of Hope (W1)
2838.9 Knockout Blow (W2)
3081.1 Rocco, Cabaretti Caterer (WRG3)
3211.2 Jewel Thief (G2)
3774.45 Elegant Entourage (G3)
3879.31 Inspiring Overseer (W2)
4160.13 Freelance Muscle (G4)
4813.54 Jaxis, the Troublemaker (R3)

*/
