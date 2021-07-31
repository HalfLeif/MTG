#pragma once

#include <iostream>
#include <map>

#include "collection.h"
#include "debug.h"
#include "test.h"

enum class Color {
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
using ManaCost = std::map<Color, int>;

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

int TotalCost(const ManaCost &cost) {
  return FindWithDefault(cost, Color::Total, 0);
}

ManaCost ParseMana(std::string mana) {
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
