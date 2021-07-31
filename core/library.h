#pragma once

#include <functional>
#include <vector>

#include "collection.h"
#include "data.h"
#include "test.h"

// TODO: deprecate the Format class.
class Library : public Format {
public:
  Deck TournamentCards(Experiment experiment_id) const override {
    return MakeDeck(experiment_id);
  }

  Deck MakeDeck(Experiment wanted_experiment_id) const {
    Deck deck;
    for (const auto &[card, experiment_id] : cards_) {
      if (experiment_id == Experiment::always ||
          experiment_id == wanted_experiment_id) {
        deck.cards.push_back(card);
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

  Color PrimaryColor() const override {
    if (colors_.empty()) {
      ERROR << "No primary color!";
      return Color::Colorless;
    }
    return colors_.front();
  }

  Color SecondaryColor() const override {
    if (colors_.size() > 1) {
      return colors_[1];
    }
    // TODO get away from this abstraction!
    return Color::Colorless;
  }

  Color TernaryColor() const override {
    if (colors_.size() > 2) {
      return colors_[2];
    }
    return Color::Colorless;
  }

  DeckSize GetDeckSize() const override { return expected_size_; };

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
    Builder &AddCard(Card c, Experiment experiment_id = Experiment::always) {
      cards_.emplace_back(c, experiment_id);
      return *this;
    }
    Builder &AddLand(Land c, Experiment experiment_id = Experiment::always) {
      lands_.emplace_back(c, experiment_id);
      return *this;
    }
    Library Build() {
      return Library(std::move(cards_), std::move(lands_), expected_size_);
    }

  private:
    DeckSize expected_size_ = DeckSize::limited;
    std::vector<std::pair<Card, Experiment>> cards_;
    std::vector<std::pair<Land, Experiment>> lands_;
  };

private:
  static void SumColorMana(const Card &card, ManaCost &mana) {
    for (const auto &[color, amount] : card.cost) {
      if (color != Color::Colorless && color != Color::Total) {
        mana[color] += amount;
      }
    }
  }

  static std::vector<Color> SortColorsByMana(const ManaCost &mana) {
    std::vector<std::pair<int, Color>> colors;
    for (const auto &[color, amount] : mana) {
      colors.emplace_back(amount, color);
    }
    std::sort(colors.begin(), colors.end(), std::greater());
    return MapFn<std::pair<int, Color>, Color>(
        colors, [](const auto &pair) { return pair.second; });
  }

  Library(std::vector<std::pair<Card, Experiment>> cards,
          std::vector<std::pair<Land, Experiment>> lands,
          DeckSize expected_size)
      : cards_(cards), lands_(lands), expected_size_(expected_size) {
    ManaCost mana;
    for (const auto &[card, experiment_id] : cards_) {
      if (experiment_id != Experiment::always) {
        active_experiments_.insert(experiment_id);
      }
      SumColorMana(card, mana);
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
  std::vector<std::pair<Card, Experiment>> cards_;
  std::vector<std::pair<Land, Experiment>> lands_;
  std::vector<Color> colors_;
};

// --------------------------------------------------------

TEST(LibraryHasSingleColorTest) {
  Library lib = Library::Builder()
                    .AddCard(MakeCard("RRR", 1, "Clockwork"))
                    .AddCard(MakeCard("4R", 1, "SearingBarrage"))
                    .Build();
  const std::vector<Color> &colors = lib.Colors();
  if (colors.size() != 1) {
    ERROR << colors.size();
    Fail("Colors has wrong size!");
    return;
  }
  if (colors[0] != Color::Red) {
    Fail("First color should be Red!");
  }
}

TEST(LibraryHasThreeColorsTest) {
  Library lib = Library::Builder()
                    .AddCard(MakeCard("U", 1, "Well"))
                    .AddCard(MakeCard("RRR", 1, "Clockwork"))
                    .AddCard(MakeCard("4R", 1, "SearingBarrage"))
                    .AddCard(MakeCard("4U", 1, "UnexplainedVision"))
                    .AddCard(MakeCard("9W", 1, "Angel"))
                    .Build();
  const std::vector<Color> &colors = lib.Colors();
  if (colors.size() != 3) {
    ERROR << colors.size();
    Fail("Colors has wrong size!");
    return;
  }
  if (colors[0] != Color::Red) {
    Fail("First color should be Red!");
  }
  if (colors[1] != Color::Blue) {
    Fail("Second color should be Blue!");
  }
  if (colors[2] != Color::White) {
    Fail("Third color should be White!");
  }
}
