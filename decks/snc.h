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
        "Freelance Muscle", "Jaxis, the Troublemaker",
        // "Hold for Ransom",
        // "Knockout Blow",
    };
  }

  std::vector<std::string_view> chosen_deck() const override {
    return {
        "Strangle",
        "For the Family",
        "Suspicious Bookcase",
        "Illuminator Virtuoso",
        "Mayhem Patrol",
        "Riveteers Requisitioner",
        "Giada, Font of Hope",
        "Hold for Ransom",
        "Antagonize",
        "High-Rise Sawjack",
        "Jewel Thief",
        "Inspiring Overseer",
        "Quick-Draw Dagger",
        "Knockout Blow",
        "Celebrity Fencer",
        "Sizzling Soloist",
        "Elegant Entourage",
        "Jaxis, the Troublemaker",
        "Wrecking Crew",
        "Pugnacious Pugilist",
        "Freelance Muscle",
        "Rocco, Cabaretti Caterer",
        "Rhox Pummeler",
    };
  }
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

Score: 56.2046
Iteration: 108
Lands { B=6 R=6 G=5 }
1345.93 Gilded Pinions (2)
1554.45 Light 'Em Up (R1)
1642.21 Capenna Express (G3)
1793.95 Mayhem Patrol (R1)
1803.27 Quick-Draw Dagger (3)
1803.27 Quick-Draw Dagger (3)
1946.45 Deal Gone Bad (B3)
2034.24 Ready to Rumble (R4)
2096.19 Corrupt Court Official (B1)
2125.64 Riveteers Requisitioner (R1)
2146.85 Wrecking Crew (R4)
2159.56 High-Rise Sawjack (G2)
2266.91 Dig Up the Body (B2)
2283.9 Sizzling Soloist (R3)
2386.02 Murder (BB1)
2941.66 Tenacious Underdog (B1)
3333.87 Jewel Thief (G2)
3367.94 Girder Goons (B4)
3388.63 Rogues' Gallery (B2)
3392.2 Freelance Muscle (G4)
3482.78 Elegant Entourage (G3)
3495.39 Pugnacious Pugilist (RR3)
4839.26 Jaxis, the Troublemaker (R3)

Score: 56.0214
Iteration: 122
Lands { W=5 R=6 G=6 }
1179.21 Hold for Ransom (W1)
1199 Strangle (R)
1500.84 Celebrity Fencer (W3)
1653.14 Light 'Em Up (R1)
1735.34 Illuminator Virtuoso (W1)
1823.08 Quick-Draw Dagger (3)
1823.08 Quick-Draw Dagger (3)
1829.8 Mayhem Patrol (R1)
2003.95 Ready to Rumble (R4)
2085.83 Ceremonial Groundbreaker (WG1)
2124.41 Wrecking Crew (R4)
2320.66 Giada, Font of Hope (W1)
2429.55 Riveteers Requisitioner (R1)
2461.51 Sizzling Soloist (R3)
2511.73 High-Rise Sawjack (G2)
2711.52 Pugnacious Pugilist (RR3)
2869.08 Knockout Blow (W2)
3417.49 Jewel Thief (G2)
3751.11 Inspiring Overseer (W2)
3872.4 Freelance Muscle (G4)
3920.4 Rocco, Cabaretti Caterer (WRG2)
3958.74 Elegant Entourage (G3)
4827.5 Jaxis, the Troublemaker (R3)

Score: 55.5872
Iteration: 124
Lands { W=6 R=6 G=6 }
1301.87 Strangle (R)
1403.68 Backup Agent (W1)
1542.32 Sky Crier (W1)
1837.42 Light 'Em Up (R1)
1862.61 Mayhem Patrol (R1)
1898.58 Illuminator Virtuoso (W1)
2011.6 Quick-Draw Dagger (3)
2011.6 Quick-Draw Dagger (3)
2011.92 Riveteers Requisitioner (R1)
2155.75 Ready to Rumble (R4)
2429.83 Sizzling Soloist (R3)
2517.64 High-Rise Sawjack (G2)
2611.3 Pugnacious Pugilist (RR3)
2632.12 Wrecking Crew (R4)
2792.9 Giada, Font of Hope (W1)
3260.74 Knockout Blow (W2)
3544.78 Jewel Thief (G2)
3638.54 Inspiring Overseer (W2)
3727.53 Freelance Muscle (G4)
3863.41 Elegant Entourage (G3)
4133.82 Rocco, Cabaretti Caterer (WRG2)
4904.24 Jaxis, the Troublemaker (R3)

Score: 55.5858
Iteration: 100
Lands { W=6 R=6 G=5 }
1494.94 Rumor Gatherer (WW1)
1586.04 Sky Crier (W1)
1599.06 Gilded Pinions (2)
1739.05 Quick-Draw Dagger (3)
1739.05 Quick-Draw Dagger (3)
1797.99 Light 'Em Up (R1)
1961.63 Capenna Express (G3)
1968.45 Celebrity Fencer (W3)
1974.98 Rhox Pummeler (G5)
1984.3 Ceremonial Groundbreaker (WG1)
2045.55 Mayhem Patrol (R1)
2171.36 High-Rise Sawjack (G2)
2176.89 Riveteers Requisitioner (R1)
2210.9 Wrecking Crew (R4)
2676.86 Giada, Font of Hope (W1)
2962.69 Pugnacious Pugilist (RR3)
3142.38 Elegant Entourage (G3)
3196.54 Knockout Blow (W2)
3225.4 Jewel Thief (G2)
3329.21 Freelance Muscle (G4)
3759.93 Inspiring Overseer (W2)
3938.94 Rocco, Cabaretti Caterer (WRG2)
4560.12 Jaxis, the Troublemaker (R3)

Score: 55.5195
Iteration: 123
Lands { B=6 R=7 G=5 }
1174.38 Strangle (R)
1376.84 Fake Your Own Death (B1)
1913.91 Light 'Em Up (R1)
1944.89 Rhox Pummeler (G5)
1963.91 Mayhem Patrol (R1)
2089.89 Quick-Draw Dagger (3)
2089.89 Quick-Draw Dagger (3)
2136.69 Ready to Rumble (R4)
2160.23 Deal Gone Bad (B3)
2187.87 Corrupt Court Official (B1)
2320.63 Riveteers Requisitioner (R1)
2329.77 Sizzling Soloist (R3)
2393.04 Wrecking Crew (R4)
2497.14 Dig Up the Body (B2)
2775.39 Tenacious Underdog (B1)
3301.95 Rogues' Gallery (B2)
3382.93 Jewel Thief (G2)
3404.78 Pugnacious Pugilist (RR3)
3622.62 Elegant Entourage (G3)
3789.22 Freelance Muscle (G4)
3854.77 Girder Goons (B4)
4907.26 Jaxis, the Troublemaker (R3)

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

*/
