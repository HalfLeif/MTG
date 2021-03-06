#pragma once

#include <chrono>
#include <cmath>
#include <map>
#include <thread>

#include "../core/game_logic.h"
#include "../core/library.h"
#include "../core/make_deck.h"

double AverageScore(const Library &lib, const Deck &deck,
                    const MulliganStrategy &strategy, int turns, int games) {
  double score = 0;
  for (int i = 0; i < games; ++i) {
    score += PlayGame(lib, deck, strategy, turns);
  }
  return score / games;
}

void SlowInsertCount(std::vector<std::pair<Land, int>> &counts,
                     const Land &land) {
  for (auto &pair : counts) {
    if (pair.first == land) {
      pair.second++;
      return;
    }
  }
  counts.emplace_back(land, 1);
}

void PrintLands(const Deck &deck) {
  std::vector<std::pair<Land, int>> land_counts;
  for (const Land &land : deck.lands) {
    SlowInsertCount(land_counts, land);
  }

  // Want lands to be sorted:
  // basic lands < non-basic lands
  // primary < secondary < ternary
  std::sort(land_counts.begin(), land_counts.end(),
            [](const auto &a, const auto &b) {
              if (a.first.type != b.first.type) {
                return a.first.type < b.first.type;
              }
              return a.first.color < b.first.color;
            });

  std::cout << "Lands { ";
  for (const auto &[land_d, count] : land_counts) {
    std::cout << land_d << "=" << count << " ";
  }
  std::cout << "}";
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
  for (int i = best_result.size() - results; i < best_result.size() && i >= 0;
       ++i) {
    const auto &param = best_result[i].param;
    Deck deck = TournamentDeck(param);

    std::cout << param.experiment << " ";
    PrintLands(deck);
    std::cout << "  -> " << best_result[i].score << "\n";
  }
}

double RunParam(const Library &lib, const Param &param, int games) {
  srand(42);
  // std::chrono::steady_clock::time_point begin =
  //     std::chrono::steady_clock::now();

  constexpr int kStart = 6;
  constexpr int kEnd = 10;

  struct Instance {
    int turns = 0;
    double score = 0;
  };

  std::vector<Instance> instances;
  for (int turns = kStart; turns <= kEnd; ++turns) {
    instances.push_back({.turns = turns});
  }

  Deck deck = TournamentDeck(param);
  std::vector<std::thread> threads;
  for (Instance &instance : instances) {
    threads.emplace_back([&]() {
      instance.score =
          AverageScore(lib, deck, SimpleStrategy, instance.turns, games);
    });
  }

  for (std::thread &thread : threads) {
    thread.join();
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

// Brute force search
Param BruteForce(const Library &lib, int turns) {
  constexpr int kGames = 20;
  std::vector<ParamResult> best_result;

  const int exp_lands = TotalLands(lib.GetDeckSize());

  // TODO: use library to count experiments.
  for (Experiment experiment : {Experiment::base, Experiment::exp}) {
    std::cout << "\n";
    for (int secondary = 0; secondary <= std::ceil(exp_lands / 2.0);
         ++secondary) {
      for (int ternary = 0;
           secondary + ternary <= std::ceil(exp_lands * 2.0 / 3); ++ternary) {
        srand(51);
        Param param = {
            .lib = &lib,
            .experiment = experiment,
            .secondary = secondary,
            .ternary = ternary,
            .deck_size = lib.GetDeckSize(),
        };
        float score = RunParam(lib, param, kGames);

        std::cout << param << "  -> score: " << score << "\n";

        best_result.push_back({
            .score = score,
            .param = param,
        });
        if (lib.TernaryColor() == Color::Colorless) {
          break;
        }
      }
      if (lib.SecondaryColor() == Color::Colorless) {
        break;
      }
    }
  }
  std::sort(best_result.begin(), best_result.end());
  PrintParamResult(best_result);
  // std::cout << "Best score: " << best_score << "\n";
  // std::cout << "Optimal " << best_param << "\n";
  return best_result.back().param;
}

std::vector<Param> GoodParams(const Library &lib) {
  std::vector<Param> solutions;
  for (Experiment exp : {Experiment::base, Experiment::exp}) {
    for (int a = 0; a <= 5; ++a) {
      for (int b = 0; b <= 5; ++b) {
        INFO << a << " " << b << "\n";
        solutions.push_back(Param{
            .lib = &lib,
            .experiment = exp,
            .secondary = a,
            .ternary = b,
            .deck_size = lib.GetDeckSize(),
        });
      }
    }
    // solutions.push_back(MakeParam(exp, 5));
    // solutions.push_back(MakeParam(exp, 6));
    // solutions.push_back(MakeParam(exp, 7));
    // solutions.push_back(MakeParam(exp, 8));
    // solutions.push_back(MakeParam(exp, 9));
  }

  return solutions;
}

Param CompareParams(const Library &lib) {
  // constexpr int kGames = 100;
  constexpr int kGames = 450;
  // constexpr int kGames = 1000;
  // constexpr int kGames = 2000;

  auto params = GoodParams(lib);
  std::vector<ParamResult> best_result;
  for (const Param &param : params) {
    double score = RunParam(lib, param, kGames);
    std::cout << param << " score: " << score << "\n";
    best_result.push_back({
        .score = score,
        .param = param,
    });
  }

  // Compare against a dummy deck as baseline.
  Library test_lib = TestLibrary();
  float dummy_score = RunParam(test_lib, {.lib = &test_lib}, kGames);
  std::cout << "Dummy score: " << dummy_score << "\n";

  std::sort(best_result.begin(), best_result.end());
  PrintParamResult(best_result);
  // std::cout << "Best score: " << best_score << "\n";
  // std::cout << "Optimal " << *optimal << "\n";
  return best_result.back().param;
}
