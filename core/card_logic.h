#pragma once

#include "deck.h"
#include "mana.h"

int DrawFromPlayedSpell(const Spell &spell, const Player &player) {
  if (spell.name == "Thief") {
    return 1;
  }
  if (spell.name == "Clockwork") {
    return 1;
  }
  if (spell.name == "LochDragon") {
    return 1;
  }
  if (spell.name == "SageOfTheFalls") {
    return 1;
  }
  if (spell.name == "UnexplainedVision") {
    return 3;
  }
  return 0;
}

double PointsFromPlayedSpell(const Spell &spell, const Player &player) {
  double points = TotalCost(spell.cost);
  if (spell.name == "Caryatid") {
    points += -1;
  } else if (spell.name == "BronzehideLion") {
    points += 1;
  } else if (spell.name == "Fenlurker") {
    points += 1;
  } else if (spell.name == "WishingWell") {
    points += 1; // scry 2
  } else if (spell.name == "Trebuchet") {
    points += 1;
  } else if (spell.name == "FireWheeler") {
    points += 1;
  } else if (spell.name == "NicolBolas") {
    points += 1;
  }
  return points;
}

double PointsFromPlayedLand(const Land &land, const Player &player) {
  if (IsSwamp(land) && Contains<Spell>(player.battlefield.spells,
                                       IsSpellName("DreadPresence"))) {
    INFO << "Played Swamp with DreadPresence in play!\n";
    return 2;
  }
  return 0;
}

void TapManaCreatures(const Deck &battlefield, ManaCost *mana_pool) {
  for (const Spell &spell : battlefield.spells) {
    if (spell.name == "Caryatid") {
      AddUniversalColor(mana_pool);
      ++(*mana_pool)[Color::Total];
    }
    if (spell.name == "SolRing") {
      // 2 gray mana, no color.
      (*mana_pool)[Color::Total] += 2;
    }
  }
}
