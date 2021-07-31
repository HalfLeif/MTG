#pragma once

#include <cmath>
#include <map>

#include "../core/data.h"
#include "../core/game_logic.h"
#include "deck.h"

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

// Brute force search
Param BruteForce(int turns) {
  constexpr int kGames = 10;
  // constexpr int kGames = 500;
  // float best_score = -1.0f;
  // Param best_param;
  std::vector<ParamResult> best_result;

  const int exp_lands = TotalLands(GetFormat().GetDeckSize());

  // TODO: use library to count experiments.
  for (Experiment experiment : {Experiment::base, Experiment::exp}) {
    std::cout << "\n";
    for (int secondary = 0; secondary <= std::ceil(exp_lands / 2.0);
         ++secondary) {
      for (int ternary = 0;
           secondary + ternary <= std::ceil(exp_lands * 2.0 / 3); ++ternary) {
        srand(51);
        Param param = {
            .experiment = experiment,
            .secondary = secondary,
            .ternary = ternary,
            .deck_size = GetFormat().GetDeckSize(),
        };
        Deck deck = TournamentDeck(param);
        float score = AverageScore(deck, SimpleStrategy, turns, kGames);

        std::cout << param << "  -> score: " << score << "\n";

        best_result.push_back({
            .score = score,
            .param = param,
        });
        // if (best_result.empty() || score > best_result.back().score) {
        // best_score = score;
        // best_param = param;
        // std::cout << "New optimal " << best_param << " score: " << score
        //           << "\n";
        // }
        if (GetFormat().TernaryColor() == Color::Colorless) {
          break;
        }
      }
      if (GetFormat().SecondaryColor() == Color::Colorless) {
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

std::vector<Param> GoodParams() {
  std::vector<Param> solutions;
  for (Experiment exp : {Experiment::base, Experiment::exp}) {
    for (int a = 0; a <= 5; ++a) {
      for (int b = 0; b <= 5; ++b) {
        INFO << a << " " << b << "\n";
        solutions.push_back(Param{
            .experiment = exp,
            .secondary = a,
            .ternary = b,
            .deck_size = GetFormat().GetDeckSize(),
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

Param CompareParams() {
  constexpr int kGames = 100;
  // constexpr int kGames = 450;
  // constexpr int kGames = 1000;
  // constexpr int kGames = 2000;
  constexpr int kStart = 6;
  // constexpr int kEnd = 8;
  // constexpr int kStart = 7;
  constexpr int kEnd = 10;
  auto params = GoodParams();
  std::vector<ParamResult> best_result;
  // float best_score = -1.0f;
  // const Param *optimal = nullptr;
  for (const Param &param : params) {
    srand(42);
    Deck deck = TournamentDeck(param);
    float score = 0.0f;
    for (int turns = kStart; turns <= kEnd; ++turns) {
      INFO << "- Run " << param << "kStart";
      score += AverageScore(deck, SimpleStrategy, turns, kGames);
      INFO << score << "\n";
    }
    std::cout << param << " score: " << score << "\n";
    // if (best_result.empty() || score > best_result.back().score) {
    best_result.push_back({
        .score = score,
        .param = param,
    });
    // if (score > best_score) {
    //   best_score = score;
    //   optimal = &param;
    // }
    // }
  }

  // Compare against dummy deck.
  Deck dummy = TestDeck();
  float dummy_score = 0.0f;
  srand(42);
  for (int turns = kStart; turns <= kEnd; ++turns) {
    dummy_score += AverageScore(dummy, SimpleStrategy, turns, kGames);
  }
  std::cout << "Dummy score: " << dummy_score << "\n";

  std::sort(best_result.begin(), best_result.end());
  PrintParamResult(best_result);
  // std::cout << "Best score: " << best_score << "\n";
  // std::cout << "Optimal " << *optimal << "\n";
  return best_result.back().param;
}
