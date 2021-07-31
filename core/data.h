#pragma once

#include <optional>

#include "collection.h"
#include "debug.h"

enum class Color {
  Total = 0, // Total converted mana cost (including Grey).
  White,
  Green,
  Red,
  Black,
  Blue,
  Colorless,
  ENUM_SIZE,
};

// Represent mana pool as how much mana could be spent per color!
// And then compare mana spent vs total mana pool. Very similar to MaxFlow
// problem. Edge case: dual W/B land + G land cannot pay for WB. Although this
// case should be rare (maybe OK for simulation purposes?).
using ManaCost = std::map<Color, int>;

void AddUniversalColor(ManaCost *mana_pool) {
  ++(*mana_pool)[Color::White];
  ++(*mana_pool)[Color::Red];
  ++(*mana_pool)[Color::Green];
  ++(*mana_pool)[Color::Black];
  ++(*mana_pool)[Color::Blue];
}

void operator+=(ManaCost &lhs, const ManaCost &rhs) {
  for (const auto &pair : rhs) {
    lhs[pair.first] += pair.second;
  }
}

template <typename K, typename V, typename M>
V FindWithDefault(const M &map, const K &key, V default_value) {
  auto it = map.find(key);
  if (it != map.end())
    return it->second;
  return default_value;
}

int TotalCost(const ManaCost &cost) {
  return FindWithDefault(cost, Color::Total, 0);
}

struct Card {
  ManaCost cost;
  int priority = 0;
  std::string name = "";
};

enum class LandType {
  basic,
  dual,
  fetch,
  shore,
};

struct Land {
  LandType type;
  Color color;
  std::optional<Color> secondary = std::nullopt;

  bool operator==(const Land &other) {
    if (type != other.type) {
      return false;
    }
    switch (type) {
    case LandType::basic:
      return color == other.color;
    case LandType::dual: {
      std::pair<Color, Color> left = {color, *secondary};
      std::pair<Color, Color> right = {other.color, *other.secondary};
      std::pair<Color, Color> right_inv = {*other.secondary, other.color};
      return (left == right) || (left == right_inv);
    }
    case LandType::fetch:
    case LandType::shore:
      // Always true if is same type.
      return true;
    }
    return true;
  }
};

struct Deck {
  std::vector<Card> cards;
  std::vector<Land> lands;
  size_t Size() { return cards.size() + lands.size(); }
};

struct Player {
  Deck library;
  Deck hand;
  Deck battlefield;
  Deck graveyard;
};

struct TurnState {
  ManaCost mana_pool;
  ManaCost agg_card_cost;
};

enum class Experiment : int {
  always, // always included.
  base,
  exp,
};

std::ostream &operator<<(std::ostream &stream, const Experiment &experiment) {
  switch (experiment) {
  case Experiment::always:
    break;
  case Experiment::base:
    stream << "base";
    break;
  case Experiment::exp:
    stream << "exp";
    break;
  }
  return stream;
}

enum class DeckSize : int {
  limited,
  constructed,
};

int TotalCards(DeckSize deck_size) {
  switch (deck_size) {
  case DeckSize::limited:
    return 40;
  case DeckSize::constructed:
    return 60;
  }
  ERROR << "Unknown DeckSize: " << static_cast<int>(deck_size);
  return -1;
}

int TotalLands(DeckSize deck_size) {
  switch (deck_size) {
  case DeckSize::limited:
    return 17;
  case DeckSize::constructed:
    return 24;
  }
  ERROR << "Unknown DeckSize: " << static_cast<int>(deck_size);
  return -1;
}

int TotalSpells(DeckSize deck_size) {
  return TotalCards(deck_size) - TotalLands(deck_size);
}

class Format {
public:
  virtual Deck TournamentCards(Experiment experiment) const = 0;
  virtual Color PrimaryColor() const = 0;
  virtual Color SecondaryColor() const = 0;
  virtual Color TernaryColor() const { return Color::Colorless; };
  virtual DeckSize GetDeckSize() const { return DeckSize::limited; };

  virtual void ManaPreference(const Player &player, const ManaCost &mana_pool,
                              std::vector<Color> *priorities) const {}
};

const Format &GetFormat();

bool IsCorpseKnight(const Card &card) { return card.name == "CorpseKnight"; }
bool IsDreadPresence(const Card &card) { return card.name == "DreadPresence"; }

bool IsBasicLand(const Land &land) { return land.type == LandType::basic; }
bool IsSwamp(const Land &land) {
  return IsBasicLand(land) && land.color == Color::Black;
}
bool IsPlains(const Land &land) {
  return IsBasicLand(land) && land.color == Color::White;
}
bool IsFetchLand(const Land &land) { return land.type == LandType::fetch; }

Land *MoveLand(int card, Deck &from, Deck &to) {
  return MoveItem<Land>(card, from.lands, to.lands);
}

Card *MoveCard(int card, Deck &from, Deck &to) {
  return MoveItem<Card>(card, from.cards, to.cards);
}

Land BasicLand(Color c) {
  return {
      .type = LandType::basic,
      .color = c,
  };
}

Land DualLand(Color c, Color secondary) {
  return {
      .type = LandType::dual,
      .color = c,
      .secondary = secondary,
  };
}

Land FetchLand() {
  return {
      .type = LandType::fetch,
      .color = Color::Colorless,
  };
}

Card MakeCard(std::string mana, int priority = 1, std::string name = "") {
  Card card;
  card.priority = priority;
  card.name = name;
  for (char c : mana) {
    if (c >= '0' && c <= '9') {
      char amount = c - '0';
      card.cost[Color::Total] += amount;
    } else if (c == 'W') {
      ++card.cost[Color::White];
      ++card.cost[Color::Total];
    } else if (c == 'B') {
      ++card.cost[Color::Black];
      ++card.cost[Color::Total];
    } else if (c == 'R') {
      ++card.cost[Color::Red];
      ++card.cost[Color::Total];
    } else if (c == 'U') {
      ++card.cost[Color::Blue];
      ++card.cost[Color::Total];
    } else if (c == 'G') {
      ++card.cost[Color::Green];
      ++card.cost[Color::Total];
    } else {
      ERROR << "Unrecognized char when parsing mana: " << c << " (" << int(c)
            << ")\n";
    }
  }
  return card;
}

// IO streaming

std::string ToString(Color color) {
  switch (color) {
  case Color::Total:
  case Color::ENUM_SIZE:
    return "";
  case Color::White:
    return "W";
  case Color::Green:
    return "G";
  case Color::Red:
    return "R";
  case Color::Black:
    return "B";
  case Color::Blue:
    return "U";
  case Color::Colorless:
    return "C";
  }
  ERROR << "Unknown color: " << static_cast<int>(color);
  return "?";
}

std::ostream &operator<<(std::ostream &stream, Color color) {
  return stream << ToString(color);
}

std::ostream &operator<<(std::ostream &stream, const ManaCost &mana) {
  for (const auto &pair : mana) {
    Color color = pair.first;
    if (color == Color::Total) {
      stream << "(" << pair.second << ")";
    } else {
      for (int i = 0; i < pair.second; ++i) {
        stream << color;
      }
    }
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const Card &card) {
  return stream << "Card " << card.cost << " " << card.name;
}

std::string ToString(const Land &land) {
  std::string result;
  switch (land.type) {
  case LandType::basic:
    return ToString(land.color);
  case LandType::dual:
    return ToString(land.color) + ToString(*land.secondary);
  case LandType::fetch:
    return "Fetch";
  case LandType::shore:
    return "Shore";
  }
  ERROR << "Unknown LandType: " << static_cast<int>(land.type);
  return "LAND?";
}

std::ostream &operator<<(std::ostream &stream, const Land &land) {
  return stream << ToString(land);
}

std::ostream &operator<<(std::ostream &stream, const Deck &deck) {
  stream << "Deck\n";
  stream << "Cards: " << deck.cards.size() << "\n";
  stream << "Lands: " << deck.lands.size() << "\n";
  for (const Card &card : deck.cards) {
    stream << "  " << card << "\n";
  }
  for (const Land &land : deck.lands) {
    stream << "  " << land << "\n";
  }
  return stream;
}
