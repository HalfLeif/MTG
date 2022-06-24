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
        "Goldhound",
        "Chrome Cat",
        "Witness Protection",
        "Fake Your Own Death", // Nice combat trick
        "Sky Crier",           // Cheap flyer (W)
        "Antagonize",          // Comat trick
        "For the Family",      // Nice combat trick
        "Speakeasy Server",
        "Mayhem Patrol",
        "Rhox Pummeler",
        "Fatal Grudge", // Kind of removal
        "Illicit Shipment",
        "Sizzling Soloist",
        "Riveteers Ascendancy",
        // p2
        "Backstreet Bruiser",
        "Deal Gone Bad",   // Removal
        "Hold for Ransom", // Nice removal (W)
        "Broken Wings",    // Removal (G)
        "Wrecking Crew",
        "Civic Gardener",
        "Masked Bandits",           // Good creature + mana fix
        "Inspiring Overseer",       // Cheap flyer (W)
        "Illuminator Virtuoso",     // Combo
        "Ceremonial Groundbreaker", // Nice Equipment (WG)
        "Public Enemy",
        "Park Heights Pegasus", // Cheap flyer (WG)
        "Rogues' Gallery",
        // p3
        "Expendable Lackey", // Can't be blocked (B)
        "Fake Your Own Death",
        "Backup Agent",
        "Ready to Rumble",
        "Halo Scarab",
        "Capenna Express",
        "Strangle", // Cheap removal (R)
        "Girder Goons",
        "Cabaretti Initiate", // Double strike with (G+R/W)
        "Elegant Entourage",
        "Out of the Way", // Kind of removal
        "Riveteers Requisitioner",
        "Evolving Door",
        // p4
        "Case the Joint",
        "Dig Up the Body",
        "Revelation of Power", // Combat trick (W)
        "Jackhammer",
        "Gilded Pinions",
        "Snooping Newsie",
        "Body Dropper",
        "High-Rise Sawjack",
        "Rumor Gatherer",
        "Hypnotic Grifter",
        "Suspicious Bookcase",     // Can't be blocked
        "Soul of Emancipation",    // Great first pick (GWU)
        "Jaxis, the Troublemaker", // Great first pick (R)
        // p5
        "Quick-Draw Dagger",      // Combat trick
        "Majestic Metamorphosis", // Combat trick
        "Corrupt Court Official",
        "Sky Crier",
        "Sticky Fingers",
        "Light 'Em Up", // Cheap removal (R)
        "Attended Socialite",
        "Murder",         // Great removal (BB)
        "Jetmir's Fixer", // Boostable (GR)
        "Rumor Gatherer",
        "Venom Connoisseur",
        "Knockout Blow", // Removal
        "Tenacious Underdog",
        // p6
        "Case the Joint",
        "Incriminate",      // Removal (B)
        "Celebrity Fencer", // Nice creature (W)
        "Sticky Fingers",
        "Quick-Draw Dagger",
        "Jewel Thief", // Nice creature (G)
        "Join the Maestros",
        "Pugnacious Pugilist",
        "Rocco, Cabaretti Caterer",
        "Freelance Muscle",    // Nice creature (G)
        "Giada, Font of Hope", // Cheap flyer (W)
        // p7 - Round 2
        "Disdainful Stroke",
        "Midnight Assassin",
        "Boon of Safety",
        "Witty Roastmaster",
        "Broken Wings",
        "Psionic Snoop",
        "Celestial Regulator",
        "Most Wanted",
        "Strangle",
        "Involuntary Employment",
        "Graveyard Shift",
        "Stimulus Package",
        // p8 - Round 3
        "Knockout Blow",
        "Raffine's Guidance",
        "Riveteers Initiate",
        "Witty Roastmaster",
        "Maestros Initiate",
        "Murder",
        "Crew Captain",
        "Sleep with the Fishes",
        "Majestic Metamorphosis",
        "Obscura Interceptor",
        "Spara's Adjudicators",
        "Attended Socialite",
        "Ominous Parcel",
        "Light 'Em Up",
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
        "Strangle", // <- "Ready to Rumble",
        "Strangle",
        "For the Family",
        "Suspicious Bookcase",
        "Sky Crier",            // <- "Hold for Ransom",
        "Park Heights Pegasus", // <- "Sky Crier",
        "Mayhem Patrol",
        "Riveteers Requisitioner",
        "Giada, Font of Hope",
        "Antagonize",
        "Jewel Thief",
        "Inspiring Overseer",
        "Witty Roastmaster", // <- "Quick-Draw Dagger",
        "Knockout Blow",
        "High-Rise Sawjack", // <- "Celebrity Fencer",
        "Sizzling Soloist",
        "Elegant Entourage",
        "Jaxis, the Troublemaker",
        "Wrecking Crew", // <- "Rhox Pummeler",
        "Pugnacious Pugilist",
        "Freelance Muscle",
        "Rocco, Cabaretti Caterer",
        "Rhox Pummeler", // <- Forest <- "Illuminator Virtuoso",
    };
  }
};

/*
Score: 57.0451
Iteration: 97
Lands { B=8 G=4 R=5 }
1080 Strangle (R)
1159.13 Mayhem Patrol (R1)
1643.13 Rhox Pummeler (G5)
1697.58 Sizzling Soloist (R3)
1765.08 Quick-Draw Dagger (3)
1813.48 Fake Your Own Death (B1)
1813.48 Fake Your Own Death (B1)
1927.75 Witty Roastmaster (R2)
1980.82 Riveteers Requisitioner (R1)
2285.24 Graveyard Shift (B4)
2515.55 Midnight Assassin (B2)
2722.39 Corrupt Court Official (B1)
2892.38 Rogues' Gallery (B2)
2987.28 Involuntary Employment (R3)
3032.47 Deal Gone Bad (B3)
3083.56 Tenacious Underdog (B1)
3134.5 Murder (BB1)
3134.5 Murder (BB1)
3149.99 Jewel Thief (G2)
3551.01 Girder Goons (B4)
3569.31 Elegant Entourage (G3)
3587.78 Freelance Muscle (G4)
4456.68 Jaxis, the Troublemaker (R3)

Score: 56.9681
Iteration: 122
Lands { B=6 G=5 R=6 }
779.008 Fatal Grudge (BR)
1317.02 Strangle (R)
1532.04 Fake Your Own Death (B1)
1615.78 Light 'Em Up (R1)
1638.1 Quick-Draw Dagger (3)
1928.57 Rhox Pummeler (G5)
1993.61 Maestros Initiate (B2)
2261.98 Witty Roastmaster (R2)
2261.98 Witty Roastmaster (R2)
2264.91 Sizzling Soloist (R3)
2300.98 Corrupt Court Official (B1)
2314.04 Riveteers Requisitioner (R1)
2411.92 Midnight Assassin (B2)
2664.23 Tenacious Underdog (B1)
2768.15 Involuntary Employment (R3)
2874.91 Deal Gone Bad (B3)
3365.77 Pugnacious Pugilist (RR3)
3400.16 Jewel Thief (G2)
3459.88 Rogues' Gallery (B2)
3523.03 Girder Goons (B4)
3523.64 Elegant Entourage (G3)
3984.74 Freelance Muscle (G4)
4700.18 Jaxis, the Troublemaker (R3)

Score: 56.5445
Iteration: 132
Lands { G=3 R=8 W=5 }
1325.88 Backup Agent (W1)
1373.27 Strangle (R)
1373.27 Strangle (R)
1775.68 Quick-Draw Dagger (3)
1775.68 Quick-Draw Dagger (3)
1839.12 Light 'Em Up (R1)
1839.12 Light 'Em Up (R1)
1955.18 Illuminator Virtuoso (W1)
2080.87 Ready to Rumble (R4)
2149.85 Riveteers Requisitioner (R1)
2310.78 Freelance Muscle (G4)
2396.18 Sizzling Soloist (R3)
2410.47 Giada, Font of Hope (W1)
2449.16 Jewel Thief (G2)
2469.97 Witty Roastmaster (R2)
2469.97 Witty Roastmaster (R2)
2677.74 Rocco, Cabaretti Caterer (WRG2)
2710.84 Elegant Entourage (G3)
2749.27 Knockout Blow (W2)
2749.27 Knockout Blow (W2)
3313.85 Inspiring Overseer (W2)
3432.41 Involuntary Employment (R3)
3849.48 Pugnacious Pugilist (RR3)
4909.25 Jaxis, the Troublemaker (R3)

Score: 56.5191
Iteration: 129
Lands { B=8 G=4 R=5 }
1149.01 Strangle (R)
1597.6 Light 'Em Up (R1)
1652.27 Crew Captain (BRG)
1722.27 Fake Your Own Death (B1)
1722.27 Fake Your Own Death (B1)
1775.02 Rhox Pummeler (G5)
1790.88 Witty Roastmaster (R2)
1790.88 Witty Roastmaster (R2)
1921.51 Riveteers Requisitioner (R1)
2341.21 Graveyard Shift (B4)
2399.07 Midnight Assassin (B2)
2470.61 Involuntary Employment (R3)
2514.17 Corrupt Court Official (B1)
2775.19 Murder (BB1)
2775.19 Murder (BB1)
2820.85 Tenacious Underdog (B1)
3055.59 Deal Gone Bad (B3)
3079.12 Jewel Thief (G2)
3472.62 Elegant Entourage (G3)
3568.13 Rogues' Gallery (B2)
3724.44 Freelance Muscle (G4)
3927.23 Girder Goons (B4)
4396.97 Jaxis, the Troublemaker (R3)

Score: 56.4921
Iteration: 130
Lands { B=5 G=4 R=7 }
1164.68 Antagonize (R1)
1278.67 Strangle (R)
1313.24 Fake Your Own Death (B1)
1673.02 Crew Captain (BRG)
1735.69 Quick-Draw Dagger (3)
1856.46 Light 'Em Up (R1)
1856.46 Light 'Em Up (R1)
1899.18 Corrupt Court Official (B1)
2087.93 Ready to Rumble (R4)
2153.43 Sizzling Soloist (R3)
2320.91 Witty Roastmaster (R2)
2320.91 Witty Roastmaster (R2)
2361.49 Riveteers Requisitioner (R1)
2480.45 Tenacious Underdog (B1)
2514.71 Midnight Assassin (B2)
2617.49 Deal Gone Bad (B3)
2692.52 Involuntary Employment (R3)
2742.92 Jewel Thief (G2)
2966.55 Girder Goons (B4)
3182.78 Freelance Muscle (G4)
3326.63 Rogues' Gallery (B2)
3375.61 Elegant Entourage (G3)
3502.55 Pugnacious Pugilist (RR3)
4832.85 Jaxis, the Troublemaker (R3)

*/
