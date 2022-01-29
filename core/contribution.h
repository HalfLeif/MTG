#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "../core/debug.h"

class Contribution;

using CardContributions =
    std::unordered_map<std::string, std::unique_ptr<Contribution>>;

class Contribution {
public:
  static const Contribution *InsertSpell(const Spell &spell,
                                         CardContributions *contributions) {
    auto [it, inserted] = contributions->try_emplace(
        spell.name, std::unique_ptr<Contribution>(new Contribution));
    ++it->second->num_cards_;
    return it->second.get();
  }

  void AddDelta(double delta) { score_ += delta; }

  // Returns contribution per card instance.
  double GetContribution() const { return score_ / num_cards(); }

  int num_cards() const {
    if (num_cards_ == 0) {
      ERROR << "Has a contribution with 0 cards." << std::endl;
      return 1;
    }
    return num_cards_;
  }

private:
  Contribution() {}

  double score_ = 0.0;
  int num_cards_ = 0;
};

CardContributions
MakeContributionMaps(const std::vector<Spell> &available_cards,
                     const std::vector<int> &permutation,
                     std::unordered_map<int, const Contribution *>
                         *permutation_to_contributions) {
  CardContributions contributions;
  for (int index : permutation) {
    const Spell &spell = available_cards[index];
    const Contribution *cptr = Contribution::InsertSpell(spell, &contributions);
    if (permutation_to_contributions != nullptr) {
      (*permutation_to_contributions)[index] = cptr;
    }
  }
  return contributions;
}

CardContributions
MakeContributionMaps(const std::vector<Spell> &available_cards) {
  CardContributions contributions;
  for (const Spell &spell : available_cards) {
    const Contribution *cptr = Contribution::InsertSpell(spell, &contributions);
  }
  return contributions;
}

void AddDelta(double delta, const std::string &name,
              CardContributions *contributions) {
  if (contributions == nullptr) {
    // Can happen in tests.
    return;
  }
  auto it = contributions->find(name);
  if (it == contributions->end()) {
    ERROR << "Spell " << name << " was not yet inserted into contributions!"
          << std::endl;
    exit(1);
    return;
  }
  it->second->AddDelta(delta);
}

double GetContribution(const std::string &name,
                       CardContributions *contributions) {
  if (contributions == nullptr) {
    return 0.0;
  }
  auto it = contributions->find(name);
  if (it != contributions->end()) {
    return it->second->GetContribution();
  }
  return 0.0;
}

void PrintContributions(const Deck &deck,
                        const CardContributions &contributions) {
  struct NamedContribution {
    const Spell *spell_ptr = nullptr;
    const Contribution *contribution_ptr = nullptr;
  };

  std::vector<std::pair<double, NamedContribution>> pairs;
  pairs.reserve(deck.spells.size());
  for (const Spell &spell : deck.spells) {
    auto it = contributions.find(spell.name);
    if (it == contributions.end()) {
      FATAL << "Could not find spell " << spell.name << " in contributions."
            << std::endl;
    }
    pairs.emplace_back(it->second->GetContribution(),
                       NamedContribution{
                           .spell_ptr = &spell,
                           .contribution_ptr = it->second.get(),
                       });
  }
  std::sort(pairs.begin(), pairs.end(),
            [](const auto &a, const auto &b) { return a.first < b.first; });

  for (const auto &[score, named] : pairs) {
    std::cout << named.contribution_ptr->GetContribution() << " "
              << named.spell_ptr->name << " (" << named.spell_ptr->cost << ")"
              << std::endl;
  }
}
