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
  if (inserted) {
    ERROR << "Spell " << name << " was not yet inserted into contributions!"
          << std::endl;
  }
}

double GetContribution(const Contribution &contribution) {
  int num_cards = contribution.num_cards;
  if (num_cards == 0) {
    num_cards = 1;
  }
  return contribution.score / num_cards;
}

double GetContribution(const std::string &name,
                       CardContributions *contributions) {
  if (contributions == nullptr) {
    return 0.0;
  }
  auto it = contributions->find(name);
  if (it != contributions->end()) {
    const Contribution &contribution = *it->second;
    return GetContribution(contribution);
  }
  return 0.0;
}

void PrintContributions(const CardContributions &contributions) {
  struct NamedContribution {
    std::string_view name = "";
    const Contribution *contribution_ptr = nullptr;
  };
  std::vector<std::pair<double, NamedContribution>> pairs;
  for (const auto &[name, contribution_ptr] : contributions) {
    pairs.emplace_back(GetContribution(*contribution_ptr),
                       NamedContribution{
                           .name = name,
                           .contribution_ptr = contribution_ptr.get(),
                       });
  }
  std::sort(pairs.begin(), pairs.end(),
            [](const auto &a, const auto &b) { return a.first < b.first; });
  for (const auto &[score, named] : pairs) {
    for (int i = 0; i < named.contribution_ptr->num_cards || i == 0; ++i) {
      std::cout << GetContribution(*named.contribution_ptr) << " " << named.name
                << std::endl;
    }
  }
}
