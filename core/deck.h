#pragma once

#include "land.h"
#include "mana.h"

struct Card {
  ManaCost cost;
  int priority = 0;
  std::string name = "";
};

Predicate<Card> IsCardName(const char *name) {
  return [name](const Card &card) { return card.name == name; };
}

struct Deck {
  std::vector<Card> cards;
  std::vector<Land> lands;
  size_t Size() { return cards.size() + lands.size(); }
};

Land *MoveLand(int card, Deck &from, Deck &to) {
  return MoveItem<Land>(card, from.lands, to.lands);
}

Card *MoveCard(int card, Deck &from, Deck &to) {
  return MoveItem<Card>(card, from.cards, to.cards);
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

bool IsCorpseKnight(const Card &card) { return card.name == "CorpseKnight"; }

Card MakeCard(std::string mana, int priority = 1, std::string name = "") {
  Card card;
  card.priority = priority;
  card.name = name;
  for (char c : mana) {
    if (c >= '0' && c <= '9') {
      char amount = c - '0';
      card.cost[Color::Total] += amount;
    } else if (c == 'W') {
      ++card.cost[Color::White];
      ++card.cost[Color::Total];
    } else if (c == 'B') {
      ++card.cost[Color::Black];
      ++card.cost[Color::Total];
    } else if (c == 'R') {
      ++card.cost[Color::Red];
      ++card.cost[Color::Total];
    } else if (c == 'U') {
      ++card.cost[Color::Blue];
      ++card.cost[Color::Total];
    } else if (c == 'G') {
      ++card.cost[Color::Green];
      ++card.cost[Color::Total];
    } else {
      ERROR << "Unrecognized char when parsing mana: " << c << " (" << int(c)
            << ")\n";
    }
  }
  return card;
}

std::ostream &operator<<(std::ostream &stream, const Card &card) {
  return stream << "Card " << card.cost << " " << card.name;
}

std::ostream &operator<<(std::ostream &stream, const Deck &deck) {
  stream << "Deck\n";
  stream << "Cards: " << deck.cards.size() << "\n";
  stream << "Lands: " << deck.lands.size() << "\n";
  for (const Card &card : deck.cards) {
    stream << "  " << card << "\n";
  }
  for (const Land &land : deck.lands) {
    stream << "  " << land << "\n";
  }
  return stream;
}
