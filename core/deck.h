#pragma once

#include "land.h"
#include "mana.h"
#include "spell.h"

Predicate<Spell> IsSpellName(const char *name) {
  return [name](const Spell &spell) { return spell.name == name; };
}

struct Deck {
  std::vector<Spell> spells;
  std::vector<Land> lands;
  size_t Size() { return spells.size() + lands.size(); }
};

struct Player {
  Deck library;
  Deck hand;
  Deck battlefield;
  Deck graveyard;
};

Land *MoveLand(int i, Deck &from, Deck &to) {
  return MoveItem<Land>(i, from.lands, to.lands);
}

Spell *MoveSpell(int i, Deck &from, Deck &to) {
  return MoveItem<Spell>(i, from.spells, to.spells);
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

std::ostream &operator<<(std::ostream &stream, const Deck &deck) {
  stream << "Deck\n";
  stream << "Spells: " << deck.spells.size() << "\n";
  stream << "Lands: " << deck.lands.size() << "\n";
  for (const Spell &spell : deck.spells) {
    stream << "  " << spell << "\n";
  }
  for (const Land &land : deck.lands) {
    stream << "  " << land << "\n";
  }
  return stream;
}
