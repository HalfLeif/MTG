#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

struct Contribution {
  double score = 0.0;
  int num_cards = 0;
};
using CardContributions =
    std::unordered_map<std::string, std::unique_ptr<Contribution>>;

CardContributions
MakeContributionMaps(const std::vector<Spell> &available_cards,
                     const std::vector<int> &permutation,
                     std::unordered_map<int, const Contribution *>
                         &permutation_to_contributions) {
  CardContributions contributions;
  for (int index : permutation) {
    const Spell &spell = available_cards[index];
    auto [it, inserted] =
        contributions.try_emplace(spell.name, std::make_unique<Contribution>());
    ++it->second->num_cards;
    permutation_to_contributions[index] = it->second.get();
  }
  return contributions;
}

void AddDelta(double delta, const std::string &name,
              CardContributions *contributions) {
  if (contributions == nullptr) {
    return;
  }
  auto [it, inserted] =
      contributions->try_emplace(name, std::make_unique<Contribution>());
  it->second->score += delta;
}

double GetContribution(const std::string &name,
                       CardContributions *contributions) {
  if (contributions == nullptr) {
    return 0.0;
  }
  auto it = contributions->find(name);
  if (it != contributions->end()) {
    const Contribution &contribution = *it->second;
    int num_cards = contribution.num_cards;
    if (num_cards == 0) {
      num_cards = 1;
    }
    return contribution.score / num_cards;
  }
  return 0.0;
}
