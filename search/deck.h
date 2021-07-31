#pragma once

#include "../core/data.h"

// TODO: make Params dynamic:
// Color primary_color;
// std::vector<std::tuple<int, Color>> secondary_lands;
// std::vector<std::tuple<bool, std::string>> other_bool_params;
// std::vector<std::tuple<int, int, std::string>> other_int_params;

// TODO: make Search dynamic based on one dynamic Param instance.
// E.g. primary_color: White, secondary_lands: {{0, Black},{0, Green}}
// struct NewParam {
//   int experiment;
//   std::vector<std::pair<Color, int>> added_lands;
// };

struct Param {
  Experiment experiment = Experiment::base;
  int secondary = 0;
  int ternary = 0;
  DeckSize deck_size = DeckSize::limited;
};

std::ostream &operator<<(std::ostream &stream, const Param &param) {
  stream << "Param experiment: " << param.experiment;
  // Note: This is an approximation since must also take into account number of
  // non-basic lands!
  const int primary_lands =
      TotalLands(param.deck_size) - param.secondary - param.ternary;
  stream << "  " << GetFormat().PrimaryColor() << "=" << primary_lands << "^";
  if (param.secondary > 0) {
    stream << "  " << GetFormat().SecondaryColor() << "=" << param.secondary;
  }
  if (param.ternary > 0) {
    stream << "  " << GetFormat().TernaryColor() << "=" << param.ternary;
  }
  return stream;
}

void FillLands(const Param &param, Deck *deck) {
  AddN(deck->lands, param.secondary, BasicLand(GetFormat().SecondaryColor()));
  AddN(deck->lands, param.ternary, BasicLand(GetFormat().TernaryColor()));

  int total = deck->lands.size() + deck->cards.size();
  int expected = TotalCards(param.deck_size);
  if (total < expected) {
    AddN(deck->lands, expected - total, BasicLand(GetFormat().PrimaryColor()));
  }
}

Deck TournamentDeck(const Param &param) {
  Deck deck = GetFormat().TournamentCards(param.experiment);
  if (deck.cards.size() != TotalSpells(param.deck_size)) {
    ERROR << "Deck cards: " << deck.cards.size() << " for " << param << "\n";
  }

  FillLands(param, &deck);
  if (deck.lands.size() != TotalLands(param.deck_size)) {
    ERROR << "Deck lands: " << deck.lands.size() << " for " << param << "\n";
  }
  return deck;
}

Deck TournamentDeck(Experiment experiment, int secondary, int ternary = 0) {
  return TournamentDeck(
      {.experiment = experiment, .secondary = secondary, .ternary = ternary});
}

Deck TestDeck() {
  Deck deck;
  AddN(deck.cards, 10, MakeCard("1B"));
  AddN(deck.cards, 10, MakeCard("1W"));
  deck.cards.push_back(MakeCard("WB"));
  deck.cards.push_back(MakeCard("1BB"));
  deck.cards.push_back(MakeCard("3BB"));

  AddN(deck.lands, 8, BasicLand(Color::White));
  AddN(deck.lands, 8, BasicLand(Color::Black));
  AddN(deck.lands, 1, FetchLand());
  return deck;
}
