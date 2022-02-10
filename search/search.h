#pragma once

#include <chrono>
#include <cmath>
#include <map>
#include <thread>

#include "../common/random.h"
#include "../core/contribution.h"
#include "../core/game_logic.h"
#include "../core/library.h"
#include "../core/make_deck.h"

double AverageScore(const Library &lib, const Deck &deck,
                    const MulliganStrategy &strategy, int turns, int games,
                    ThreadsafeRandom &rand,
                    CardContributions *contributions = nullptr) {
  double score = 0;
  for (int i = 0; i < games; ++i) {
    score += PlayGame(lib, deck, strategy, turns, rand, contributions);
  }
  return score / games;
}

struct ParamResult {
  double score;
  Param param;

  bool operator<(const ParamResult &other) const {
    return this->score < other.score;
  }
};

void PrintParamResult(const std::vector<ParamResult> best_result,
                      int results = 10) {
  std::cout << "\n";
  if (best_result.size() < results) {
    // Can happen if very few results.
    results = best_result.size();
  }
  for (int i = best_result.size() - results; i < best_result.size(); ++i) {
    const auto &param = best_result[i].param;
    Deck deck = TournamentDeck(param);

    std::cout << param.experiment << " ";
    PrintLands(deck);
    std::cout << "  -> " << best_result[i].score << "\n";
  }
}

double RunParam(const Library &lib, const Param &param, int games,
                ThreadsafeRandom &rand,
                CardContributions *contributions = nullptr) {
  // std::chrono::steady_clock::time_point begin =
  //     std::chrono::steady_clock::now();

  // Always evaluate using 8 turns. Seems to provide the most fair comparison.
  constexpr int kStart = 8;
  constexpr int kEnd = 8;

  struct Instance {
    int turns = 0;
    double score = 0;
  };

  std::vector<Instance> instances;
  for (int turns = kStart; turns <= kEnd; ++turns) {
    instances.push_back({.turns = turns});
  }

  Deck deck = TournamentDeck(param);
  for (Instance &instance : instances) {
    instance.score = AverageScore(lib, deck, SimpleStrategy, instance.turns,
                                  games, rand, contributions);
  }
  double score = 0;
  for (const Instance &instance : instances) {
    score += instance.score;
  }

  // std::chrono::steady_clock::time_point end =
  //     std::chrono::steady_clock::now();
  // std::cout << "Run Par = "
  //      << std::chrono::duration_cast<std::chrono::milliseconds>(end -
  //      begin)
  //             .count()
  //      << "[ms]" << std::endl;

  return score;
}

// Attempts to populate good parameters based on the Library format.
std::vector<Param> GoodParams(const Library &lib) {
  const int total_lands = TotalLands(lib.GetDeckSize());

  std::vector<Param> solutions;
  for (Experiment exp : lib.ActiveExperiments()) {
    int wanted_lands = total_lands - lib.NumLandsPresent(exp);

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
        INFO << secondary << " " << ternary << "\n";
        solutions.push_back(Param{
            .lib = &lib,
            .experiment = exp,
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
    solutions.push_back({.lib = &lib, .experiment = exp, .secondary = 7});
    solutions.push_back({.lib = &lib, .experiment = exp, .secondary = 8});
    solutions.push_back({.lib = &lib, .experiment = exp, .secondary = 9});
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
    double score = RunParam(lib, param, games, rand);
    if (print) {
      std::cout << param << " score: " << score << "\n";
    }

    best_result.push_back({
        .score = score,
        .param = param,
    });
  }

  // Compare against a dummy deck as baseline.
  if (print) {
    Library test_lib = TestLibrary();
    float dummy_score = RunParam(test_lib, {.lib = &test_lib}, games, rand);
    std::cout << "Dummy score: " << dummy_score << "\n";
  }

  std::sort(best_result.begin(), best_result.end());
  if (print) {
    PrintParamResult(best_result);
  }

  return best_result.back().param;
}
