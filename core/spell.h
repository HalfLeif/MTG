#pragma once

#include <string>

#include "mana.h"

struct Spell {
  ManaCost cost;
  int priority = 0;
  std::string name = "";
};

Spell MakeSpell(std::string mana, int priority = 1, std::string name = "") {
  Spell spell;
  spell.priority = priority;
  spell.name = name;
  for (char c : mana) {
    if (c >= '0' && c <= '9') {
      char amount = c - '0';
      spell.cost[Color::Total] += amount;
    } else if (c == 'W') {
      ++spell.cost[Color::White];
      ++spell.cost[Color::Total];
    } else if (c == 'B') {
      ++spell.cost[Color::Black];
      ++spell.cost[Color::Total];
    } else if (c == 'R') {
      ++spell.cost[Color::Red];
      ++spell.cost[Color::Total];
    } else if (c == 'U') {
      ++spell.cost[Color::Blue];
      ++spell.cost[Color::Total];
    } else if (c == 'G') {
      ++spell.cost[Color::Green];
      ++spell.cost[Color::Total];
    } else {
      ERROR << "Unrecognized char when parsing mana: " << c << " (" << int(c)
            << ")\n";
    }
  }
  return spell;
}

std::ostream &operator<<(std::ostream &stream, const Spell &spell) {
  return stream << "spell " << spell.cost << " " << spell.name;
}
