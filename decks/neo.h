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
        // "When We Were Young",
        "Automated Artificer",
        "The Shattered States Era",
        "Towashi Songshaper",
        "Clawing Torment",
        "Moonsnare Specialist",
        "The Reality Chip",
        "Anchor to Reality",
        "Mnemonic Sphere",
        "Akki Ronin",
        // "Dramatist's Puppet",
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
        // "Eater of Virtue", // one less, don't want to have two.
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
        // "Enormous Energy Blade",
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

  std::vector<std::string_view> chosen_deck() const override {
    return {
        "Era of Enlightenment",
        "Era of Enlightenment",
        "Dokuchi Shadow-Walker",
        //
        "Eater of Virtue",
        "Eater of Virtue",
        // "When We Were Young",
        "When We Were Young",
        "Wanderer's Intervention",
        "Wanderer's Intervention",
        "Lethal Exploit",
        "Imperial Oath",
        "Chainflail Centipede",
        "Virus Beetle",
        "Kami of Terrible Secrets",
        "Dokuchi Silencer",
        "Michiko's Reign of Truth",
        "Repel the Vile",
        "Sunblade Samurai",
        "Seven-Tail Mentor",
        "Seven-Tail Mentor",
        "Circuit Mender",
        "Circuit Mender",
        "Biting-Palm Ninja",
        "Tatsunari, Toad Rider",
        "Junji, the Midnight Sky",
    };
  };

  int MinColors() const override { return 2; }
  int MaxColors() const override { return 2; }

  // Colors the generator can use for building a deck.
  std::vector<Color> AvailableColors() const override {
    return {
        Color::Black, // Color::White,
        Color::Green, Color::Blue,
        // Color::Red
    };
  }
};

/* Round 1

Note: Even better with { W=8 B=8 }
Score: 58.5363
Iteration: 48
Lands { W=7 B=9 }
1215.46 Era of Enlightenment (W1)
1390.46 Dokuchi Shadow-Walker (BB4)
1579.41 Eater of Virtue (1)
1579.41 Eater of Virtue (1)
1587.15 When We Were Young (W3)
1587.15 When We Were Young (W3)
1697.63 Wanderer's Intervention (W1)
1697.63 Wanderer's Intervention (W1)
1831.49 Lethal Exploit (B1)
1871.74 Imperial Oath (W5)
1961.05 Chainflail Centipede (B2)
2050.99 Virus Beetle (B1)
2434.29 Kami of Terrible Secrets (B3)
2619.76 Dokuchi Silencer (B1)
2697.43 Michiko's Reign of Truth (W1)
2813.11 Repel the Vile (W3)
3136.28 Sunblade Samurai (W4)
3246.75 Seven-Tail Mentor (W3)
3246.75 Seven-Tail Mentor (W3)
3452.61 Circuit Mender (3)
3452.61 Circuit Mender (3)
4141.99 Biting-Palm Ninja (B2)
4504.23 Tatsunari, Toad Rider (B2)
4540.97 Junji, the Midnight Sky (BB3)

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

Score: 58.4915
Iteration: 81
Lands { B=9 G=8 }
739.584 Dramatist's Puppet (4)
1281.03 Automated Artificer (2)
1292.11 Webspinner Cuff (G2)
1611.81 Grafted Growth (G2)
1697.75 Eater of Virtue (1)
1697.75 Eater of Virtue (1)
1757.32 Chainflail Centipede (B2)
1995.89 Fade into Antiquity (G2)
1997.6 Dokuchi Shadow-Walker (BB4)
2093.17 Lethal Exploit (B1)
2131.77 Virus Beetle (B1)
2262.42 Mukotai Ambusher (B3)
2451.64 Careful Cultivation (G2)
2562.99 Dokuchi Silencer (B1)
2899.07 Kami of Terrible Secrets (B3)
3188.44 Circuit Mender (3)
3188.44 Circuit Mender (3)
3775.73 Gloomshrieker (BG1)
4132 Biting-Palm Ninja (B2)
4147.05 Blossom Prancer (GG3)
4479.4 Boseiju Reaches Skyward (G3)
4775.57 Tatsunari, Toad Rider (B2)
4864.98 Junji, the Midnight Sky (BB3)

Score: 58.4404
Iteration: 55
Lands { U=8 B=10 }
1055.82 March of Swirling Mist (U2)
1151.81 Mirrorshell Crab (UU5)
1171.89 Automated Artificer (2)
1514.36 Suit Up (U2)
1772.48 Lethal Exploit (B1)
1793.31 Eater of Virtue (1)
1869.29 Dokuchi Shadow-Walker (BB4)
1930.77 Go-Shintai of Lost Wisdom (U1)
2192.51 Chainflail Centipede (B2)
2393.1 Virus Beetle (B1)
2595.03 Mukotai Ambusher (B3)
2635.71 Dokuchi Silencer (B1)
2725.62 Prosperous Thief (U2)
3220.35 Kami of Terrible Secrets (B3)
3283.75 The Reality Chip (U1)
3614.73 Circuit Mender (3)
3614.73 Circuit Mender (3)
3992.85 Kairi, the Swirling Sky (UU4)
4087.59 Biting-Palm Ninja (B2)
4315.64 Tatsunari, Toad Rider (B2)
4577.98 Moonsnare Specialist (U3)
5214.07 Junji, the Midnight Sky (BB3)

Score: 58.2404
Iteration: 57
Lands { U=8 B=9 }
624.917 Mirrorshell Crab (UU5)
1157.99 March of Swirling Mist (U2)
1264.6 Ninja's Kunai (1)
1466.15 Mnemonic Sphere (U1)
1534.35 Dokuchi Shadow-Walker (BB4)
1651.17 Eater of Virtue (1)
1783.93 Moon-Circuit Hacker (U1)
1866.42 Lethal Exploit (B1)
2079.76 Go-Shintai of Lost Wisdom (U1)
2179.02 Chainflail Centipede (B2)
2207.38 Virus Beetle (B1)
2417.35 Dokuchi Silencer (B1)
2678.99 Mukotai Ambusher (B3)
2737.31 Prosperous Thief (U2)
3133.61 Kairi, the Swirling Sky (UU4)
3195.16 Kami of Terrible Secrets (B3)
3463.96 The Reality Chip (U1)
3613.93 Circuit Mender (3)
3613.93 Circuit Mender (3)
4014.22 Biting-Palm Ninja (B2)
4392.59 Tatsunari, Toad Rider (B2)
4521.5 Moonsnare Specialist (U3)
4877.17 Junji, the Midnight Sky (BB3)


*/
