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
};

/* Round 1
Score: 56.6039
Iteration: 91
Lands { W=4 B=8 G=6 }
1239.29 Wanderer's Intervention (W1)
1682.91 Eater of Virtue (1)
1682.91 Eater of Virtue (1)
1863.28 Chainflail Centipede (B2)
1926.43 Lethal Exploit (B1)
1939.42 Repel the Vile (W3)
2056.66 Careful Cultivation (G2)
2073.7 Michiko's Reign of Truth (W1)
2078.25 Virus Beetle (B1)
2081.73 Fade into Antiquity (G2)
2511.21 Dokuchi Silencer (B1)
2567.17 Seven-Tail Mentor (W3)
2567.17 Seven-Tail Mentor (W3)
2746.01 Kami of Terrible Secrets (B3)
3101.21 Sunblade Samurai (W4)
3298.99 Blossom Prancer (GG3)
3368.05 Circuit Mender (3)
3368.05 Circuit Mender (3)
3700.23 Gloomshrieker (BG1)
4251.59 Tatsunari, Toad Rider (B2)
4330.26 Boseiju Reaches Skyward (G3)
4739.35 Junji, the Midnight Sky (BB3)

Score: 56.0909
Iteration: 105
Lands { W=5 B=7 G=4 }
1249.23 Era of Enlightenment (W1)
1435.57 Wanderer's Intervention (W1)
1515.63 Fade into Antiquity (G2)
1600.11 Eater of Virtue (1)
1600.11 Eater of Virtue (1)
1678.24 Lethal Exploit (B1)
1805.03 Careful Cultivation (G2)
1921.93 Mukotai Ambusher (B3)
1979.79 Chainflail Centipede (B2)
2037.6 Blossom Prancer (GG3)
2094.78 Virus Beetle (B1)
2316.42 Kami of Terrible Secrets (B3)
2318.9 Michiko's Reign of Truth (W1)
2368.02 Dokuchi Silencer (B1)
2599.81 Repel the Vile (W3)
2826.09 Seven-Tail Mentor (W3)
2826.09 Seven-Tail Mentor (W3)
2836.67 Sunblade Samurai (W4)
2931.03 Gloomshrieker (BG1)
3295.19 Boseiju Reaches Skyward (G3)
3380.76 Circuit Mender (3)
3380.76 Circuit Mender (3)
3858.32 Tatsunari, Toad Rider (B2)
3893.32 Junji, the Midnight Sky (BB3)

Score: 55.8117
Iteration: 113
Lands { W=6 B=8 G=6 }
1055.16 Return to Action (B1)
1586.97 Grafted Growth (G2)
1811.25 Lethal Exploit (B1)
2027.17 Chainflail Centipede (B2)
2081.02 Fade into Antiquity (G2)
2150.95 Virus Beetle (B1)
2451.84 Repel the Vile (W3)
2615.39 Dokuchi Silencer (B1)
2696.72 Michiko's Reign of Truth (W1)
2801.3 Imperial Oath (W5)
3206.81 Gloomshrieker (BG1)
3237.93 Seven-Tail Mentor (W3)
3237.93 Seven-Tail Mentor (W3)
3341.64 Circuit Mender (3)
3341.64 Circuit Mender (3)
3505.54 Blossom Prancer (GG3)
3627.13 Sunblade Samurai (W4)
4460.76 Tatsunari, Toad Rider (B2)
4750.78 Junji, the Midnight Sky (BB3)
4767.32 Boseiju Reaches Skyward (G3)

*/
