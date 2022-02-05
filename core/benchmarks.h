#pragma once

#include "../core/benchmark.h"
#include "../core/library.h"
#include "../core/make_deck.h"
#include "../decks/mid.h"
#include "../search/search.h"

/*
BENCHMARK(PushbackReserve) {
  std::vector<int> v;
  v.reserve(100);
  for (int i = 0; i < 100; ++i) {
    v.push_back(i);
  }
}

BENCHMARK(Pushback) {
  std::vector<int> v;
  for (int i = 0; i < 100; ++i) {
    v.push_back(i);
  }
}

BENCHMARK(Pushfront) {
  std::vector<int> v;
  for (int i = 0; i < 100; ++i) {
    v.insert(v.begin(), i);
  }
}
*/

// Runs 100 games for a given Library and Param.
// Before: 3.22 ms per iteration.
BENCHMARK(RunParam) {
  const Library &lib = kMID;
  // CardContributions contributions = MakeContributionMaps(lib.spells);
  Param param = {
      .lib = &lib,
      .secondary = 8,
  };
  RunParam(lib, param, 100, /*contributions=*/nullptr);
}
