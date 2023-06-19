#pragma once

#include <map>
#include <set>
#include <utility>
#include <vector>

#include "../core/mana.h"
#include "../core/spell.h"

struct CardSummary {
  int num_above_average = 0;
  int num_below_average = 0;
  double total_bonus = 0;

  CardSummary &operator+=(const CardSummary &other) {
    this->num_above_average += other.num_above_average;
    this->num_below_average += other.num_below_average;
    this->total_bonus += other.total_bonus;
    return *this;
  }
};

std::ostream &operator<<(std::ostream &stream, const CardSummary &summary) {
  return stream << "bonus: " << summary.total_bonus << std::endl           //
                << "num_above: " << summary.num_above_average << std::endl //
                << "num_below: " << summary.num_below_average;
}

std::vector<std::pair<ManaCost, CardSummary>>
AggregateAndSortColors(const std::map<ManaCost, CardSummary> &summaries) {
  std::vector<std::pair<ManaCost, CardSummary>> result;
  for (auto &[colors, summary] : summaries) {
    CardSummary aggregate = summary;
    int count = 0;
    for (const ManaCost &mono : colors.MonoColors()) {
      ++count;
      // Add all mono color summaries.
      aggregate += summaries.at(mono);
    }
    aggregate.total_bonus /= (count + 1);
    result.emplace_back(colors, aggregate);
  }
  std::sort(result.begin(), result.end(), [](const auto &a, const auto &b) {
    return a.second.total_bonus > b.second.total_bonus;
  });
  return result;
}

void PrintSummaries(
    const std::vector<std::pair<ManaCost, CardSummary>> &summaries) {
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
  std::vector<std::pair<ManaCost, CardSummary>> aggregate =
      AggregateAndSortColors(summaries);
  PrintSummaries(aggregate);
  PrintStrongestCards(std::move(available_cards));
}
