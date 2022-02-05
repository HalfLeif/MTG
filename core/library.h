#pragma once

#include <functional>
#include <memory>
#include <set>
#include <vector>

#include "collection.h"
#include "deck.h"
#include "mana.h"
#include "test.h"

enum class Experiment : int {
  always, // always included.
  base,
  exp,
  exp2,
  exp3,
  exp4,
};

std::ostream &operator<<(std::ostream &stream, const Experiment &experiment) {
  switch (experiment) {
  case Experiment::always:
    break;
  case Experiment::base:
    stream << "base";
    break;
  case Experiment::exp:
    stream << "exp";
    break;
  case Experiment::exp2:
    stream << "exp2";
    break;
  case Experiment::exp3:
    stream << "exp3";
    break;
  case Experiment::exp4:
    stream << "exp4";
    break;
  }
  return stream;
}

class Library {
public:
  Deck MakeDeck(Experiment wanted_experiment_id) const {
    Deck deck;
    for (const auto &[spell, experiment_id] : spells_) {
      if (experiment_id == Experiment::always ||
          experiment_id == wanted_experiment_id) {
        deck.spells.push_back(spell);
      }
    }
    for (const auto &[land, experiment_id] : lands_) {
      if (experiment_id == Experiment::always ||
          experiment_id == wanted_experiment_id) {
        deck.lands.push_back(land);
      }
    }
    return deck;
  }

  const std::vector<Color> &Colors() const { return colors_; }

  Color PrimaryColor() const {
    if (colors_.empty()) {
      ERROR << "No primary color!";
      return Color::Colorless;
    }
    return colors_.front();
  }

  Color SecondaryColor() const {
    if (colors_.size() > 1) {
      return colors_[1];
    }
    // TODO get away from this abstraction!
    return Color::Colorless;
  }

  Color TernaryColor() const {
    if (colors_.size() > 2) {
      return colors_[2];
    }
    return Color::Colorless;
  }

  DeckSize GetDeckSize() const { return expected_size_; };

  int NumLandsPresent(Experiment exp_id) const {
    int count = 0;
    for (const auto &[land, experiment] : lands_) {
      if (experiment == exp_id || experiment == Experiment::always) {
        ++count;
      }
    }
    return count;
  }

  std::set<Experiment> ActiveExperiments() const {
    std::set<Experiment> active;
    for (const auto &[_, experiment] : lands_) {
      if (experiment != Experiment::always) {
        active.insert(experiment);
      }
    }
    for (const auto &[_, experiment] : spells_) {
      if (experiment != Experiment::always) {
        active.insert(experiment);
      }
    }
    if (active.empty()) {
      // If no active experiments, should return a single value to iterate on.
      active.insert(Experiment::always);
    }
    return active;
  }

  // Returns the maximum number of alterantives this Library supports.
  // Note: this is actually broken now...
  // int NumExperiments() const { return 1 + max_experiment_id_; }

  class Builder {
  public:
    Builder &SetLimited() {
      expected_size_ = DeckSize::limited;
      return *this;
    }
    Builder &SetConstructed() {
      expected_size_ = DeckSize::constructed;
      return *this;
    }
    Builder &AddSpell(Spell c, Experiment experiment_id = Experiment::always) {
      spells_.emplace_back(c, experiment_id);
      return *this;
    }
    Builder &AddLand(Land c, Experiment experiment_id = Experiment::always) {
      lands_.emplace_back(c, experiment_id);
      return *this;
    }
    Library Build() {
      return Library(std::move(spells_), std::move(lands_), expected_size_);
    }

    std::unique_ptr<Library> BuildUnique() {
      return std::unique_ptr<Library>(
          new Library(std::move(spells_), std::move(lands_), expected_size_));
    }

  private:
    DeckSize expected_size_ = DeckSize::limited;
    std::vector<std::pair<Spell, Experiment>> spells_;
    std::vector<std::pair<Land, Experiment>> lands_;
  };

private:
  static std::vector<Color> SortColorsByMana(const ManaCost &mana) {
    std::vector<std::pair<int, Color>> colors;
    for (const auto &[color, amount] : mana) {
      if (color == Color::Total) {
        continue;
      }
      colors.emplace_back(amount, color);
    }
    std::sort(colors.begin(), colors.end(),
              std::greater<std::pair<int, Color>>());
    return MapFn<std::pair<int, Color>, Color>(
        colors, [](const auto &pair) { return pair.second; });
  }

  Library(std::vector<std::pair<Spell, Experiment>> spells,
          std::vector<std::pair<Land, Experiment>> lands,
          DeckSize expected_size)
      : spells_(spells), lands_(lands), expected_size_(expected_size) {
    ManaCost mana;
    for (const auto &[spell, experiment_id] : spells_) {
      if (experiment_id != Experiment::always) {
        active_experiments_.insert(experiment_id);
      }
      mana += spell.cost;
    }
    colors_ = SortColorsByMana(mana);

    for (const auto &[land, experiment_id] : lands_) {
      if (experiment_id != Experiment::always) {
        active_experiments_.insert(experiment_id);
      }
    }
  }

  DeckSize expected_size_;
  std::set<Experiment> active_experiments_;
  std::vector<std::pair<Spell, Experiment>> spells_;
  std::vector<std::pair<Land, Experiment>> lands_;
  std::vector<Color> colors_;
};

// --------------------------------------------------------

TEST(LibraryHasSingleColorTest) {
  Library lib = Library::Builder()
                    .AddSpell(MakeSpell("RRR", 1, "Clockwork"))
                    .AddSpell(MakeSpell("4R", 1, "SearingBarrage"))
                    .Build();
  const std::vector<Color> &colors = lib.Colors();
  EXPECT_EQ(colors.size(), 1);
  EXPECT_EQ(colors[0], Color::Red);
}

TEST(LibraryHasThreeColorsTest) {
  Library lib = Library::Builder()
                    .AddSpell(MakeSpell("U", 1, "Well"))
                    .AddSpell(MakeSpell("RRR", 1, "Clockwork"))
                    .AddSpell(MakeSpell("4R", 1, "SearingBarrage"))
                    .AddSpell(MakeSpell("4U", 1, "UnexplainedVision"))
                    .AddSpell(MakeSpell("9W", 1, "Angel"))
                    .Build();
  const std::vector<Color> &colors = lib.Colors();
  EXPECT_EQ(colors.size(), 3);
  EXPECT_EQ(colors[0], Color::Red);
  EXPECT_EQ(colors[1], Color::Blue);
  EXPECT_EQ(colors[2], Color::White);
}
