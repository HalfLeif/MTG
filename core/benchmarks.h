#pragma once

#include "benchmark.h"

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
