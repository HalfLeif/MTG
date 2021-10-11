#pragma once

#include <optional>
#include <string>

#include "mana.h"
#include "test.h"

struct Spell {
  ManaCost cost;
  std::optional<ManaCost> ability;
  std::optional<ManaCost> onetime_ability;

  int priority = 0;
  double point_bonus = 0;
  std::string name = "";

  Spell &AddAbility(std::string mana_cost) {
    ability = ParseMana(mana_cost);
    return *this;
  }

  Spell &AddOnetimeAbility(std::string mana_cost) {
    onetime_ability = ParseMana(mana_cost);
    return *this;
  }

  Spell &AddBonus(double bonus) {
    point_bonus = bonus;
    return *this;
  }
};

Spell MakeSpell(std::string mana_cost, int priority = 1,
                std::string name = "") {
  Spell spell;
  spell.priority = priority;
  spell.name = name;
  spell.cost = ParseMana(mana_cost);
  return spell;
}

std::ostream &operator<<(std::ostream &stream, const Spell &spell) {
  return stream << "spell " << spell.cost << " " << spell.name;
}

// -----------------------------------------------------------------------------

TEST(AbilityCost) {
  Spell s = MakeSpell("B").AddAbility("BB");
  if (ToString(s.cost) != "B") {
    Fail("Expected B but got " + ToString(s.cost));
  }
  if (!s.ability.has_value() or ToString(*s.ability) != "BB") {
    Fail("Expected BB but got " + ToString(*s.ability));
  }
}
