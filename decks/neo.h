#pragma once

#include <string_view>
#include <vector>

#include "../core/sealed_deck.h"

// Neon Dynasty (2022)
class Neo : public SealedDeck {
public:
  std::string_view data_path() const override { return "data/neo/cards.csv"; }

  std::vector<std::string_view> cards() const override {
    return {
        "Akki Ember-Keeper",
        "Lucky Offering",
        "Suit Up",
        "Ninja's Kunai",
        "Biting-Palm Ninja",
        "Go-Shintai of Lost Wisdom",
        "When We Were Young",
        "Circuit Mender",
        "Kairi, the Swirling Sky",
        "When We Were Young",
        "Automated Artificer",
        "The Shattered States Era",
        "Towashi Songshaper",
        "Clawing Torment",
        "Moonsnare Specialist",
        "The Reality Chip",
        "Anchor to Reality",
        "Mnemonic Sphere",
        "Akki Ronin",
        "Dramatist's Puppet",
        "Explosive Entry",
        "Go-Shintai of Ancient Wars",
        "Eater of Virtue",
        "Webspinner Cuff",
        "Grafted Growth",
        "Mothrider Patrol",
        "Crackling Emergence",
        "Careful Cultivation",
        "Moon-Circuit Hacker",
        "Twinshot Sniper",
        "Eater of Virtue",
        "Prosperous Thief",
        "Lethal Exploit",
        "Mirrorshell Crab",
        "Crackling Emergence",
        "Uncharted Haven",
        "Dokuchi Silencer",
        "Boseiju, Who Endures",
        "Generous Visitor",
        "Chainflail Centipede",
        "Wanderer's Intervention",
        "Seven-Tail Mentor",
        "Imperial Oath",
        "Roadside Reliquary",
        "Circuit Mender",
        "Peerless Samurai",
        "Era of Enlightenment",
        "Heir of the Ancient Fang",
        "Seven-Tail Mentor",
        "Scrapyard Steelbreaker",
        "Boseiju Reaches Skyward",
        "March of Swirling Mist",
        "Roadside Reliquary",
        "Ninja's Kunai",
        "Peerless Samurai",
        "Light the Way",
        "Virus Beetle",
        "Blossoming Sands",
        "Explosive Singularity",
        "Invigorating Hot Spring",
        "Repel the Vile",
        "Return to Action",
        "Mukotai Ambusher",
        "Experimental Synthesizer",
        "Wanderer's Intervention",
        "Enormous Energy Blade",
        "Junji, the Midnight Sky",
        "Blossom Prancer",
        "Fade into Antiquity",
        "Moonsnare Prototype",
        "Kami of Terrible Secrets",
        "Era of Enlightenment",
        "Michiko's Reign of Truth",
        "Tatsunari, Toad Rider",
        "Gloomshrieker",
        "Ancestral Katana",
        "Dokuchi Shadow-Walker",
        "Sunblade Samurai",
        "Towashi Songshaper",
        "Simian Sling",
    };
  }

  std::vector<std::string_view> forced_cards() const override {
    return {
        "Junji, the Midnight Sky",
        "Kami of Terrible Secrets",
        "Eater of Virtue",
    };
  }
};

/* Round 1

Score: 58.6629
Iteration: 93
Lands { U=8 B=10 }
1040.21 March of Swirling Mist (U2)
1549.11 Suit Up (U2)
1658.57 Moon-Circuit Hacker (U1)
1680.5 Eater of Virtue (1)
1680.5 Eater of Virtue (1)
1907.42 Dokuchi Shadow-Walker (BB4)
1950.38 Lethal Exploit (B1)
1999.77 Go-Shintai of Lost Wisdom (U1)
2158.38 Virus Beetle (B1)
2221.73 Chainflail Centipede (B2)
2525.71 Dokuchi Silencer (B1)
2591.59 Mukotai Ambusher (B3)
2615.7 Prosperous Thief (U2)
3190.75 The Reality Chip (U1)
3201.36 Kami of Terrible Secrets (B3)
3745.29 Kairi, the Swirling Sky (UU4)
3856.73 Circuit Mender (3)
3856.73 Circuit Mender (3)
4203.64 Biting-Palm Ninja (B2)
4318.39 Tatsunari, Toad Rider (B2)
4614.42 Moonsnare Specialist (U3)
5262.54 Junji, the Midnight Sky (BB3)

Score: 58.3989
Iteration: 94
Lands { U=8 B=11 }
1178.52 Automated Artificer (2)
1696.71 Eater of Virtue (1)
1696.71 Eater of Virtue (1)
1703.13 Moon-Circuit Hacker (U1)
2104.66 Lethal Exploit (B1)
2138.74 Go-Shintai of Lost Wisdom (U1)
2367.39 Prosperous Thief (U2)
2382.45 Virus Beetle (B1)
2383.66 Chainflail Centipede (B2)
2472.28 Dokuchi Shadow-Walker (BB4)
2482.94 Dokuchi Silencer (B1)
2831.77 Mukotai Ambusher (B3)
3012.49 The Reality Chip (U1)
3473.69 Kami of Terrible Secrets (B3)
3599.4 Circuit Mender (3)
3599.4 Circuit Mender (3)
3838.12 Kairi, the Swirling Sky (UU4)
4466.63 Tatsunari, Toad Rider (B2)
4492.34 Moonsnare Specialist (U3)
4928.28 Biting-Palm Ninja (B2)
5376.04 Junji, the Midnight Sky (BB3)

Score: 58.3507
Iteration: 113
Lands { W=8 B=10 }
1359.48 When We Were Young (W3)
1596.32 Era of Enlightenment (W1)
1687.01 Wanderer's Intervention (W1)
1729.14 Eater of Virtue (1)
1729.14 Eater of Virtue (1)
2015.57 Dokuchi Shadow-Walker (BB4)
2039.13 Mukotai Ambusher (B3)
2064.03 Lethal Exploit (B1)
2088.12 Virus Beetle (B1)
2553.57 Dokuchi Silencer (B1)
2573.44 Imperial Oath (W5)
2688.96 Kami of Terrible Secrets (B3)
2805.97 Repel the Vile (W3)
3043.57 Michiko's Reign of Truth (W1)
3296.61 Seven-Tail Mentor (W3)
3296.61 Seven-Tail Mentor (W3)
3402.8 Circuit Mender (3)
3402.8 Circuit Mender (3)
3647.98 Sunblade Samurai (W4)
4099.34 Biting-Palm Ninja (B2)
4480.79 Tatsunari, Toad Rider (B2)
5313.28 Junji, the Midnight Sky (BB3)

Score: 58.1002
Iteration: 104
Lands { W=7 B=9 }
1150.59 Ninja's Kunai (1)
1314.93 Era of Enlightenment (W1)
1343.43 Dokuchi Shadow-Walker (BB4)
1600.06 Wanderer's Intervention (W1)
1600.06 Wanderer's Intervention (W1)
1654.28 Eater of Virtue (1)
1654.28 Eater of Virtue (1)
1847.1 Mukotai Ambusher (B3)
1938.16 Chainflail Centipede (B2)
1973.57 Imperial Oath (W5)
1979.65 Lethal Exploit (B1)
2080.1 Virus Beetle (B1)
2388.73 Kami of Terrible Secrets (B3)
2594.04 Dokuchi Silencer (B1)
2720.17 Repel the Vile (W3)
3005.24 Michiko's Reign of Truth (W1)
3032.88 Sunblade Samurai (W4)
3339.91 Seven-Tail Mentor (W3)
3339.91 Seven-Tail Mentor (W3)
3431.34 Circuit Mender (3)
3431.34 Circuit Mender (3)
3848.81 Biting-Palm Ninja (B2)
4529.14 Tatsunari, Toad Rider (B2)
4553.99 Junji, the Midnight Sky (BB3)

Score: 57.9875
Iteration: 100
Lands { W=5 U=7 B=6 }
1392.38 Era of Enlightenment (W1)
1622.19 Eater of Virtue (1)
1622.19 Eater of Virtue (1)
1693.45 Moon-Circuit Hacker (U1)
2009.24 Go-Shintai of Lost Wisdom (U1)
2034.01 Imperial Oath (W5)
2145.3 Dokuchi Silencer (B1)
2378.65 Michiko's Reign of Truth (W1)
2434.16 Repel the Vile (W3)
2553.26 Prosperous Thief (U2)
2706.92 Kami of Terrible Secrets (B3)
2853.15 Sunblade Samurai (W4)
2947.68 Seven-Tail Mentor (W3)
2947.68 Seven-Tail Mentor (W3)
3152.82 The Reality Chip (U1)
3342.11 Circuit Mender (3)
3342.11 Circuit Mender (3)
3485.62 Junji, the Midnight Sky (BB3)
3690.23 Kairi, the Swirling Sky (UU4)
3917.35 Biting-Palm Ninja (B2)
3918.24 Tatsunari, Toad Rider (B2)
4142.22 Moonsnare Specialist (U3)

Score: 57.8119
Iteration: 124
Lands { W=5 U=5 B=8 }
1713.96 Eater of Virtue (1)
1713.96 Eater of Virtue (1)
1728.27 Mukotai Ambusher (B3)
1809.61 Lethal Exploit (B1)
1960.7 Chainflail Centipede (B2)
1984.89 Virus Beetle (B1)
2041.09 Prosperous Thief (U2)
2218.68 Michiko's Reign of Truth (W1)
2336.01 Imperial Oath (W5)
2421.26 Dokuchi Silencer (B1)
2446.09 The Reality Chip (U1)
2686.98 Kami of Terrible Secrets (B3)
2770.66 Repel the Vile (W3)
2865.92 Seven-Tail Mentor (W3)
2865.92 Seven-Tail Mentor (W3)
3148.35 Sunblade Samurai (W4)
3421.28 Circuit Mender (3)
3421.28 Circuit Mender (3)
3796.6 Moonsnare Specialist (U3)
4024.28 Biting-Palm Ninja (B2)
4479.13 Tatsunari, Toad Rider (B2)
4516.44 Junji, the Midnight Sky (BB3)

*/
