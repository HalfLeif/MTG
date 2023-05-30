#pragma once

#include "land.h"
#include "mana.h"
#include "spell.h"

Predicate<SpellView> IsSpellName(const char *name) {
  return [name](const SpellView &spell) { return spell.name() == name; };
}

struct Deck {
  std::vector<SpellView> spells;
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

SpellView *MoveSpell(int i, Deck &from, Deck &to) {
  return MoveItem<SpellView>(i, from.spells, to.spells);
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

void SlowInsertCount(std::vector<std::pair<Land, int>> &counted_lands,
                     const Land &land) {
  for (auto &pair : counted_lands) {
    if (land == pair.first) {
      ++pair.second;
      return;
    }
  }
  counted_lands.emplace_back(land, 1);
}

void PrintLands(const Deck &deck) {
  std::vector<std::pair<Land, int>> land_counts;
  for (const Land &land : deck.lands) {
    SlowInsertCount(land_counts, land);
  }

  // Want lands to be sorted:
  // basic lands < non-basic lands
  // primary < secondary < tertiary
  std::sort(land_counts.begin(), land_counts.end(),
            [](const auto &a, const auto &b) {
              if (a.first.type != b.first.type) {
                return a.first.type < b.first.type;
              }

              // Making these strings once per comparison is obviously
              // expensive. However, printing lands is not a frequent operation.
              return ToString(a.first) < ToString(b.first);
            });

  std::cout << "Lands { ";
  for (const auto &[land_d, count] : land_counts) {
    std::cout << land_d << "=" << count << " ";
  }
  std::cout << "}" << std::endl;
}

std::ostream &operator<<(std::ostream &stream, const Deck &deck) {
  stream << "Deck\n";
  stream << "Spells: " << deck.spells.size() << "\n";
  stream << "Lands: " << deck.lands.size() << "\n";
  PrintLands(deck);
  for (SpellView spell_view : deck.spells) {
    stream << "  " << spell_view << "\n";
  }
  return stream;
}
