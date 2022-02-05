#pragma once

#include <chrono>
#include <iostream>
#include <vector>

// Uses template rather than base class to avoid virtual call at each iteration.
template <typename Op> void ExecuteBenchmark(std::string_view name) {
  std::cout << "Benchmark " << name << std::endl;
  Op op;

  const std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();

  constexpr int kEstimateIterations = 50;
  for (int r = 0; r < kEstimateIterations; ++r) {
    op();
  }
  const std::chrono::steady_clock::time_point estimate_end =
      std::chrono::steady_clock::now();
  const std::chrono::duration estimate_duration = estimate_end - begin;
  const std::chrono::duration single_run =
      estimate_duration / kEstimateIterations;
  const std::chrono::duration wanted_total = std::chrono::seconds(1);
  const int iterations_left = (wanted_total - estimate_duration) / single_run;
  // std::cout << "Estimation run suggest we can do " << iterations_left
  //           << " more iterations" << std::endl;

  for (int r = 0; r < iterations_left; ++r) {
    op();
  }

  const std::chrono::steady_clock::time_point end =
      std::chrono::steady_clock::now();
  const std::chrono::duration total_duration = end - begin;
  const int total_iterations = iterations_left + kEstimateIterations;
  std::cout << "Run " << total_iterations << " iterations in "
            << std::chrono::duration_cast<std::chrono::milliseconds>(
                   total_duration)
                   .count()
            << " ms" << std::endl;

  std::chrono::duration per_run_total = total_duration / total_iterations;
  int nanos =
      std::chrono::duration_cast<std::chrono::nanoseconds>(per_run_total)
          .count();
  std::cout << "Run average time per iteration: "
            << (static_cast<double>(nanos) * 0.001) << " us" << std::endl
            << std::endl;
}

class BenchmarkRegistration {
public:
  // Uses std::function for registration purposes. Each fn corresponds to
  // running ExecuteBenchmark<>.
  using BenchmarkFn = std::function<void()>;
  void Register(BenchmarkFn b) { benchmarks_.push_back(b); }

  void RunAll() {
    for (const auto &fn : benchmarks_) {
      fn();
    }
  }

  static BenchmarkRegistration &Singleton() {
    static BenchmarkRegistration *kSingleton = new BenchmarkRegistration();
    return *kSingleton;
  }

private:
  std::vector<BenchmarkFn> benchmarks_;
};

class Benchmark {
public:
  Benchmark(BenchmarkRegistration::BenchmarkFn fn) {
    BenchmarkRegistration::Singleton().Register(std::move(fn));
  }
};

#define BENCHMARK(name)                                                        \
  struct BenchmarkOp##name {                                                   \
    void operator()();                                                         \
  };                                                                           \
  Benchmark benchmark_instance##name(                                          \
      []() { ExecuteBenchmark<BenchmarkOp##name>(#name); });                   \
  void BenchmarkOp##name::operator()()

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
