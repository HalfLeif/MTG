#pragma once

#include <iostream>
#include <map>

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

int TotalCost(const ManaCost &cost) {
  return FindWithDefault(cost, Color::Total, 0);
}

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
