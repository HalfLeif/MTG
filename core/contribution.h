#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "../common/debug.h"
#include "../core/deck.h"
#include "../core/spell.h"

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
    it->second->mana_value_ = spell.cost.FindValue(Color::Total);
    return it->second.get();
  }

  void AddDelta(double delta) { score_ += delta; }

  // Returns contribution per card instance.
  double GetContribution() const { return score_ / num_cards(); }

  int mana_value() const { return mana_value_; }

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
  int mana_value_ = 0;
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

// For tests.
CardContributions
MakeContributionMaps(const std::vector<SpellView> &available_cards) {
  CardContributions contributions;
  for (const SpellView spell : available_cards) {
    const Contribution *cptr =
        Contribution::InsertSpell(*spell, &contributions);
  }
  return contributions;
}

void AddDelta(double delta, const std::string &name,
              CardContributions *contributions) {
  if (contributions == nullptr) {
    // Can happen in tests.
    return;
  }
  Contribution *contribution = FindPtrOrNull(*contributions, name);
  if (contribution == nullptr) {
    FATAL << "Spell " << name << " was not yet inserted into contributions!"
          << std::endl;
  }
  contribution->AddDelta(delta);
}

double GetContribution(const std::string &name,
                       const CardContributions *contributions) {
  if (contributions == nullptr) {
    return 0.0;
  }
  Contribution *contribution = FindPtrOrNull(*contributions, name);
  if (contribution != nullptr) {
    return contribution->GetContribution();
  }
  return 0.0;
}

void PrintContributions(const Deck &deck,
                        const CardContributions &contributions) {
  struct NamedContribution {
    SpellView spell;
    const Contribution *contribution_ptr = nullptr;
  };

  // Key by 1. mana_value, 2. contribution.
  std::vector<std::pair<double, NamedContribution>> pairs;
  pairs.reserve(deck.spells.size());
  for (const SpellView spell : deck.spells) {
    const Contribution *contribution =
        FindPtrOrNull(contributions, spell.name());
    if (contribution == nullptr) {
      FATAL << "Could not find spell " << spell.name() << " in contributions."
            << std::endl;
    }
    pairs.emplace_back(contribution->GetContribution(),
                       NamedContribution{
                           .spell = spell,
                           .contribution_ptr = contribution,
                       });
  }
  std::sort(pairs.begin(), pairs.end(),
            [](const auto &a, const auto &b) { return a.first < b.first; });

  for (const auto &[score, named] : pairs) {
    printf("%8.0f ", named.contribution_ptr->GetContribution());
    std::cout << named.spell.name() << " (" << named.spell.cost() << ")"
              << std::endl;
  }
}
