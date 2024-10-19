#pragma once

#include <optional>
#include <string>

#include "../common/test.h"
#include "mana.h"

struct Spell {
  ManaCost cost;
  std::optional<ManaCost> ability;
  std::optional<ManaCost> onetime_ability;

  char priority = 0;
  double point_bonus = 0;
  int pick_order = 0;
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

  // TODO add mana ability - tap for mana
};

struct SpellView {
  SpellView(const Spell &spell) : spell_(&spell) {}
  // Should not be able to create dangling spell views.
  SpellView(Spell &&src) = delete;

  const std::string &name() const { return spell_->name; }
  const ManaCost &cost() const { return spell_->cost; }
  const std::optional<ManaCost> &ability() const { return spell_->ability; }

  void use_onetime_ability() { used_onetime_ = true; }
  const ManaCost *onetime_ability() const {
    if (!used_onetime_ && spell_->onetime_ability.has_value()) {
      return &*spell_->onetime_ability;
    }
    return nullptr;
  }

  bool has_value() const { return spell_ != nullptr; }
  const Spell &operator*() const { return *spell_; }
  const Spell *operator->() const { return spell_; }

private:
  bool used_onetime_ = false;
  const Spell *spell_ = nullptr;
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

std::ostream &operator<<(std::ostream &stream, SpellView view) {
  if (view.has_value()) {
    stream << *view;
  } else {
    stream << "nullptr spell";
  }
  return stream;
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
