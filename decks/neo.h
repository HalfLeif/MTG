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
};

/* Round 1
Score: 57.6053
Iteration: 123
Lands { B=9 G=7 }
1018.66 Heir of the Ancient Fang (G2)
1185.54 Automated Artificer (2)
1191.31 Ninja's Kunai (1)
1191.31 Ninja's Kunai (1)
1212.35 Return to Action (B1)
1560.78 Eater of Virtue (1)
1560.78 Eater of Virtue (1)
1639.45 Webspinner Cuff (G2)
1906.78 Lethal Exploit (B1)
1988.93 Chainflail Centipede (B2)
2124.15 Fade into Antiquity (G2)
2272.75 Virus Beetle (B1)
2398.78 Mukotai Ambusher (B3)
2488.38 Careful Cultivation (G2)
2731.07 Dokuchi Silencer (B1)
3115.67 Kami of Terrible Secrets (B3)
3455.73 Circuit Mender (3)
3455.73 Circuit Mender (3)
3484.75 Blossom Prancer (GG3)
3485.81 Gloomshrieker (BG1)
3919.99 Biting-Palm Ninja (B2)
4302.58 Junji, the Midnight Sky (BB3)
4345.4 Boseiju Reaches Skyward (G3)
4572.64 Tatsunari, Toad Rider (B2)

Score: 57.5121
Iteration: 50
Lands { W=10 B=9 }
1473.87 Era of Enlightenment (W1)
1566.85 When We Were Young (W3)
1698.55 Wanderer's Intervention (W1)
1698.55 Wanderer's Intervention (W1)
1799.76 Lethal Exploit (B1)
1870.5 Mukotai Ambusher (B3)
2096.8 Virus Beetle (B1)
2111.76 Dokuchi Shadow-Walker (BB4)
2482.95 Dokuchi Silencer (B1)
2581.38 Kami of Terrible Secrets (B3)
3048.88 Repel the Vile (W3)
3051.94 Imperial Oath (W5)
3134.75 Michiko's Reign of Truth (W1)
3267.27 Circuit Mender (3)
3267.27 Circuit Mender (3)
3476.68 Seven-Tail Mentor (W3)
3476.68 Seven-Tail Mentor (W3)
3816.57 Sunblade Samurai (W4)
4359.25 Biting-Palm Ninja (B2)
4622.11 Tatsunari, Toad Rider (B2)
5200.26 Junji, the Midnight Sky (BB3)

Score: 56.8266
Iteration: 88
Lands { U=5 B=6 G=5 }
1206.81 Ninja's Kunai (1)
1229.09 Mnemonic Sphere (U1)
1643.93 Eater of Virtue (1)
1643.93 Eater of Virtue (1)
1685.27 Grafted Growth (G2)
1714.17 Kairi, the Swirling Sky (UU4)
1740.54 Lethal Exploit (B1)
1756.02 Go-Shintai of Lost Wisdom (U1)
1916.01 Virus Beetle (B1)
1920.55 Chainflail Centipede (B2)
2070.46 Prosperous Thief (U2)
2186.5 Blossom Prancer (GG3)
2229.72 Mukotai Ambusher (B3)
2369.51 Dokuchi Silencer (B1)
2607.85 The Reality Chip (U1)
2761.31 Kami of Terrible Secrets (B3)
2874.16 Junji, the Midnight Sky (BB3)
3019.2 Gloomshrieker (BG1)
3348.81 Circuit Mender (3)
3348.81 Circuit Mender (3)
3753.96 Moonsnare Specialist (U3)
3814.39 Biting-Palm Ninja (B2)
3888.8 Boseiju Reaches Skyward (G3)
4022.81 Tatsunari, Toad Rider (B2)

*/
