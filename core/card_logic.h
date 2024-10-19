#pragma once

#include "contribution.h"
#include "deck.h"
#include "mana.h"

int DrawFromPlayedSpell(const SpellView spell, const Player &player) {
  if (spell.name() == "Thief") {
    return 1;
  }
  if (spell.name() == "Clockwork") {
    return 1;
  }
  if (spell.name() == "LochDragon") {
    return 1;
  }
  if (spell.name() == "SageOfTheFalls") {
    return 1;
  }
  if (spell.name() == "UnexplainedVision") {
    return 3;
  }
  return 0;
}

double PointsFromPlayedLand(const Land &land, const Player &player,
                            CardContributions *contributions) {
  if (IsSwamp(land) && Contains<SpellView>(player.battlefield.spells,
                                           IsSpellName("DreadPresence"))) {
    INFO << "Played Swamp with DreadPresence in play!\n";
    AddDelta(2, "DreadPresence", contributions);
    return 2;
  }
  return land.bonus;
}

void TapManaCreatures(const Deck &battlefield, ManaCost *mana_pool) {
  for (const SpellView spell : battlefield.spells) {
    if (spell.name() == "Caryatid" ||
        spell.name() == "PatchworkBanner") {
      AddUniversalColor(mana_pool);
      ++(*mana_pool)[Color::Total];
    }
    if (spell.name() == "SolRing") {
      // 2 gray mana, no color.
      (*mana_pool)[Color::Total] += 2;
    }
  }
}
