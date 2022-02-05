#pragma once

#include <cstdint>
#include <iostream>
#include <map>
#include <string_view>

#include "collection.h"
#include "debug.h"
#include "test.h"

enum class Color : int8_t {
  Total = 0, // Total converted mana cost (including Grey).
  White,
  Blue,
  Black,
  Red,
  Green,
  Colorless,
  ENUM_SIZE,
};

// Represent mana pool as how much mana could be spent per color!
// And then compare mana spent vs total mana pool. Very similar to MaxFlow
// problem. Edge case: dual W/B land + G land cannot pay for WB. Although this
// case should be rare (maybe OK for simulation purposes?).
class ManaCost {
public:
  using key_type = Color;
  using mapped_type = int;

  auto find(const key_type &c) const { return cost_.find(c); }
  auto begin() const { return cost_.begin(); }
  auto end() const { return cost_.end(); }
  mapped_type &operator[](const key_type &key) { return cost_[key]; }

private:
  // TODO: Replace with std::array<int, Color::ENUM_SIZE>;
  std::map<Color, int> cost_;
};

void AddUniversalColor(ManaCost *mana_pool) {
  ++(*mana_pool)[Color::White];
  ++(*mana_pool)[Color::Blue];
  ++(*mana_pool)[Color::Black];
  ++(*mana_pool)[Color::Red];
  ++(*mana_pool)[Color::Green];
}

void operator+=(ManaCost &lhs, const ManaCost &rhs) {
  for (const auto &pair : rhs) {
    lhs[pair.first] += pair.second;
  }
}

void UpdateMaxColors(ManaCost &mana_needs, const ManaCost &spell_needs) {
  for (const auto [color, amount] : spell_needs) {
    mana_needs[color] = std::max(mana_needs[color], amount);
  }
}

int TotalCost(const ManaCost &cost) {
  return FindWithDefault(cost, Color::Total, 0);
}

ManaCost ParseMana(std::string_view mana) {
  ManaCost cost;
  for (char c : mana) {
    if (c >= '0' && c <= '9') {
      char amount = c - '0';
      cost[Color::Total] += amount;
    } else if (c == 'W') {
      ++cost[Color::White];
      ++cost[Color::Total];
    } else if (c == 'U') {
      ++cost[Color::Blue];
      ++cost[Color::Total];
    } else if (c == 'B') {
      ++cost[Color::Black];
      ++cost[Color::Total];
    } else if (c == 'R') {
      ++cost[Color::Red];
      ++cost[Color::Total];
    } else if (c == 'G') {
      ++cost[Color::Green];
      ++cost[Color::Total];
    } else if (c == 'X') {
      // TODO: use actual X mana.
      cost[Color::Total] += 2;
    } else {
      ERROR << "Unrecognized char when parsing mana: " << c << " (" << int(c)
            << ")\n";
    }
  }
  return cost;
}

std::string ToString(Color color) {
  switch (color) {
  case Color::Total:
  case Color::ENUM_SIZE:
    return "";
  case Color::White:
    return "W";
  case Color::Blue:
    return "U";
  case Color::Black:
    return "B";
  case Color::Red:
    return "R";
  case Color::Green:
    return "G";
  case Color::Colorless:
    return "C";
  }
  ERROR << "Unknown color: " << static_cast<int>(color);
  return "?";
}

std::ostream &operator<<(std::ostream &stream, Color color) {
  return stream << ToString(color);
}

std::string ToString(const ManaCost &mana) {
  std::string result = "";
  int color_mana_sum = 0;
  for (int c = static_cast<int>(Color::White);
       c < static_cast<int>(Color::ENUM_SIZE); ++c) {
    Color color = static_cast<Color>(c);
    int num_color = FindWithDefault(mana, color, 0);
    if (num_color > 0) {
      color_mana_sum += num_color;
      std::string color_str = ToString(color);
      for (int i = 0; i < num_color; ++i) {
        result.append(color_str);
      }
    }
  }
  int colorless_mana = FindWithDefault(mana, Color::Total, 0) - color_mana_sum;
  if (colorless_mana < 0) {
    ERROR << "Should never happen!";
  }
  if (colorless_mana > 0) {
    result.append(std::to_string(colorless_mana));
  }
  return result;
}

std::ostream &operator<<(std::ostream &stream, const ManaCost &mana) {
  return stream << ToString(mana);
}

// -----------------------------------------------------------------------------

TEST(ParseManaSimple) {
  std::string s = ToString(ParseMana("B3"));
  if (s != "B3") {
    Fail("Expected B3 but found " + s);
  }
}

TEST(ParseManaRepeat) {
  std::string s = ToString(ParseMana("BB"));
  if (s != "BB") {
    Fail("Expected BB but found " + s);
  }
}

TEST(ParseManaMulti) {
  std::string s = ToString(ParseMana("BBG2"));
  if (s != "BBG2") {
    Fail("Expected BBG2 but found " + s);
  }
}
