#pragma once

#include "../common/benchmark.h"
#include "../common/random.h"
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
// Run 1429 iterations in 1946 ms
// Run average time per iteration: 1.361 ms
BENCHMARK(RunParam) {
  ThreadsafeRandom rand;
  const Library &lib = kMID;
  // CardContributions contributions = MakeContributionMaps(lib.spells);
  Param param = {
      .lib = &lib,
      .secondary = 8,
  };
  RunParam(lib, param, 100, rand, /*contributions=*/nullptr);
}
