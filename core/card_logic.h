#pragma once

#include "format.h"

int DrawFromPlayedCard(const Card &card, const Player &player) {
  if (card.name == "Thief") {
    return 1;
  }
  if (card.name == "Clockwork") {
    return 1;
  }
  if (card.name == "LochDragon") {
    return 1;
  }
  if (card.name == "SageOfTheFalls") {
    // TODO: also draw if has SageOfTheFalls and plays non-human.
    return 1;
  }
  if (card.name == "UnexplainedVision") {
    return 3;
  }
  return 0;
}

int PointsFromPlayedCard(const Card &card, const Player &player) {
  if (card.name == "Caryatid") {
    return -1;
  }
  if (card.name == "BronzehideLion") {
    return 1;
  }
  if (card.name == "Fenlurker") {
    return 1;
  }
  if (card.name == "WishingWell") {
    return 1; // scry 2
  }
  if (card.name == "Trebuchet") {
    return 1;
  }
  if (card.name == "FireWheeler") {
    return 2;
  }
  if (card.name == "NicolBolas") {
    return 2;
  }
  return 0;
}

double PointsFromPlayedLand(const Land &land, const Player &player) {
  if (IsSwamp(land) &&
      Contains<Card>(player.battlefield.cards, IsDreadPresence)) {
    INFO << "Played Swamp with DreadPresence in play!\n";
    return 2;
  }
  // if (land.type == LandType::dual) {
  //   return 0.5;
  // }
  return 0;
}

void TapManaCreatures(const Deck &battlefield, ManaCost *mana_pool) {
  for (const Card &card : battlefield.cards) {
    if (card.name == "Caryatid") {
      AddUniversalColor(mana_pool);
      ++(*mana_pool)[Color::Total];
    }
    if (card.name == "SolRing") {
      // 2 gray mana, no color.
      (*mana_pool)[Color::Total] += 2;
    }
  }
}
