#pragma once

#include <map>
#include <set>
#include <utility>

#include "../core/mana.h"
#include "../core/spell.h"

struct CardSummary {
  int num_above_average = 0;
  int num_below_average = 0;
  double total_bonus = 0;
};

std::ostream &operator<<(std::ostream &stream, const CardSummary &summary) {
  return stream << "bonus: " << summary.total_bonus << std::endl           //
                << "num_above: " << summary.num_above_average << std::endl //
                << "num_below: " << summary.num_below_average;
}

void PrintSummaries(const std::map<ManaCost, CardSummary> &summaries) {
  std::cout << "Summary" << std::endl;
  for (const auto &[colors, summary] : summaries) {
    std::cout << std::endl << colors << std::endl << summary << std::endl;
  }
  std::cout << std::endl;
}

void PrintStrongestCards(std::vector<Spell> cards) {
  std::sort(cards.begin(), cards.end(), [](const Spell &l, const Spell &r) {
    return l.pick_order < r.pick_order;
  });
  constexpr int kMaxCardsToPrint = 30;
  std::cout << "Best cards" << std::endl;
  for (int i = 0; i < kMaxCardsToPrint && i < cards.size(); ++i) {
    std::cout << "\t" << cards[i] << " #" << cards[i].pick_order << std::endl;
  }
  std::cout << std::endl;
}

void ShowTop(const std::vector<Spell> &all_cards, const SealedDeck *sealed) {
  std::vector<Spell> available_cards = FilterCards(all_cards, sealed->cards());

  std::map<ManaCost, CardSummary> summaries;
  for (const Spell &spell : available_cards) {
    ManaCost unique_colors = spell.cost.GetColors();
    CardSummary &summary = summaries[unique_colors];
    if (spell.point_bonus > 0) {
      ++summary.num_above_average;
      summary.total_bonus += spell.point_bonus;
    } else {
      ++summary.num_below_average;
    }
  }
  PrintSummaries(summaries);
  PrintStrongestCards(std::move(available_cards));
}
