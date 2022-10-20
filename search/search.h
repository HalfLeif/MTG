#pragma once

#include <chrono>
#include <cmath>
#include <cstdio>
#include <map>
#include <ostream>
#include <thread>

#include "../common/random.h"
#include "../core/contribution.h"
#include "../core/game_logic.h"
#include "../core/library.h"
#include "../core/param.h"

class Metrics {
public:
  Metrics() {
    // Needs to support default construction.
    mean_ = 0;
    stddev_ = 0;
  }
  Metrics(const std::vector<double> &scores) {
    CHECK(scores.size() > 1);
    double sum = 0;
    for (double score : scores) {
      sum += score;
    }
    mean_ = sum / scores.size();

    // Sample variance = S_x (x - mean)^2 / (N - 1)
    double variance = 0;
    for (double score : scores) {
      variance += std::pow(score - mean_, 2);
    }
    variance /= (scores.size() - 1);
    stddev_ = sqrt(variance);
  }

  double score() const { return mean_ - stddev_; }
  double mean() const { return mean_; }
  double stddev() const { return stddev_; }

  bool operator<(const Metrics &other) const {
    return this->score() < other.score();
  }
  bool operator>(const Metrics &other) const {
    return this->score() > other.score();
  }

private:
  double mean_;
  double stddev_;
};

std::ostream &operator<<(std::ostream &s, const Metrics &metrics) {
  // Not really printing to the stream but good enough for now.
  printf("%.1f (%.1f - %.1f)", metrics.score(), metrics.mean(),
         metrics.stddev());
  return s;
}

Metrics AverageScore(const Library &lib, const Deck &deck,
                     const MulliganStrategy &strategy, int turns, int games,
                     ThreadsafeRandom &rand,
                     CardContributions *contributions = nullptr) {
  std::vector<double> scores;
  scores.reserve(games);

  for (int i = 0; i < games; ++i) {
    scores.push_back(PlayGame(lib, deck, strategy, turns, rand, contributions));
  }
  return Metrics(scores);
}

struct ParamResult {
  Metrics metrics;
  Param param;
  CardContributions contributions;

  bool operator<(const ParamResult &other) const {
    return this->metrics.score() < other.metrics.score();
  }
};

void PrintParamResult(const std::vector<ParamResult> &best_result,
                      int results = 10) {
  std::cout << std::endl;
  if (best_result.size() < results) {
    // Can happen if very few results.
    results = best_result.size();
  }
  for (int i = best_result.size() - results; i < best_result.size(); ++i) {
    const auto &param = best_result[i].param;
    Deck deck = TournamentDeck(param);

    std::cout << best_result[i].metrics << " ";
    if (param.experiment != Experiment::always) {
      std::cout << param.experiment << " ";
    }
    PrintLands(deck);

    if (i == best_result.size() - 1) {
      // The best result
      std::cout << std::endl;
      PrintContributions(deck, best_result[i].contributions);
    }
  }
}

Metrics RunParam(const Library &lib, const Param &param, int games,
                 ThreadsafeRandom &rand, CardContributions *contributions) {
  constexpr int kTurns = 10;

  Deck deck = TournamentDeck(param);
  if (contributions->empty()) {
    // For mana eval.
    *contributions = MakeContributionMaps(deck.spells);
  }

  return AverageScore(lib, deck, SimpleStrategy, kTurns, games, rand,
                      contributions);
}

// Attempts to populate good parameters based on the Library format.
std::vector<Param> GoodParams(const Library &lib) {
  std::vector<Param> solutions;
  for (Experiment exp : lib.ActiveExperiments()) {
    // If have less than 23 spells in the deck, should fill up with lands, even
    // if gets 18 or more lands.
    const int existing_cards =
        lib.NumLandsPresent(exp) + lib.NumSpellsPresent(exp);
    const int remaining_lands = TotalCards(lib.GetDeckSize()) - existing_cards;

    int wanted_lands = remaining_lands;
    int max_ternary_lands = 1 + wanted_lands / 3;
    if (lib.TernaryColor() == Color::Colorless) {
      max_ternary_lands = 0;
    }
    wanted_lands -= max_ternary_lands;
    int max_secondary_lands = 1 + wanted_lands / 2;
    if (lib.SecondaryColor() == Color::Colorless) {
      max_secondary_lands = 0;
    }

    for (int secondary = 0; secondary <= max_secondary_lands; ++secondary) {
      for (int ternary = 0; ternary <= max_ternary_lands; ++ternary) {
        int primary = remaining_lands - secondary - ternary;
        INFO << secondary << " " << ternary << "\n";
        solutions.push_back(Param{
            .lib = &lib,
            .experiment = exp,
            .primary = primary,
            .secondary = secondary,
            .ternary = ternary,
            .deck_size = lib.GetDeckSize(),
        });
      }
    }
  }

  return solutions;
}

std::vector<Param> ManualParams(const Library &lib) {
  // Can be tweaked for a detailed run of best params.
  std::vector<Param> solutions;
  for (Experiment exp : lib.ActiveExperiments()) {
    solutions.push_back(
        {.lib = &lib, .experiment = exp, .primary = 10, .secondary = 7});
  }
  return solutions;
}

Param CompareParams(const Library &lib, ThreadsafeRandom &rand, int games = 450,
                    bool print = true) {
  // constexpr int kGames = 100;
  // constexpr int kGames = 450;
  // constexpr int kGames = 1000;
  // constexpr int kGames = 2000;

  // std::vector<Param> params = ManualParams(lib);
  std::vector<Param> params = GoodParams(lib);
  std::vector<ParamResult> best_result;
  for (const Param &param : params) {
    CardContributions contributions;
    Metrics metrics = RunParam(lib, param, games, rand, &contributions);
    if (print) {
      std::cout << param << " score: " << metrics << "\n";
    }

    best_result.push_back({
        .metrics = metrics,
        .param = param,
        .contributions = std::move(contributions),
    });
  }

  std::sort(best_result.begin(), best_result.end());
  if (print) {
    PrintParamResult(best_result);
  }

  return best_result.back().param;
}

// -----------------------------------------------------------------------------

TEST(GoodParamsWithStandardDeck) {
  Library::Builder builder;
  for (int i = 0; i < TotalSpells(DeckSize::limited); ++i) {
    if (i % 2 == 0) {
      builder.AddSpell(MakeSpell("B2"));
    } else {
      builder.AddSpell(MakeSpell("W3"));
    }
  }
  Library lib = builder.Build();
  std::vector<Param> params = GoodParams(lib);
  EXPECT_LT(0, params.size());
  for (Param p : params) {
    EXPECT_EQ(p.primary + p.secondary, TotalLands(DeckSize::limited));
  }
}

TEST(GoodParamsWithFewerSpells) {
  Library::Builder builder;
  int num_spells = TotalSpells(DeckSize::limited) - 1;
  for (int i = 0; i < num_spells; ++i) {
    if (i % 2 == 0) {
      builder.AddSpell(MakeSpell("B2"));
    } else {
      builder.AddSpell(MakeSpell("W3"));
    }
  }
  Library lib = builder.Build();
  std::vector<Param> params = GoodParams(lib);
  EXPECT_LT(0, params.size());
  for (Param p : params) {
    EXPECT_EQ(p.primary + p.secondary, 1 + TotalLands(DeckSize::limited));
  }
}

TEST(GoodParamsWithCustomLand) {
  Library::Builder builder;
  for (int i = 0; i < TotalSpells(DeckSize::limited); ++i) {
    if (i % 2 == 0) {
      builder.AddSpell(MakeSpell("B2"));
    } else {
      builder.AddSpell(MakeSpell("W3"));
    }
  }
  builder.AddLand(DualLand(Color::White, Color::Black));

  Library lib = builder.Build();
  std::vector<Param> params = GoodParams(lib);
  EXPECT_LT(0, params.size());
  for (Param p : params) {
    EXPECT_EQ(p.primary + p.secondary, TotalLands(DeckSize::limited) - 1);
  }
}
