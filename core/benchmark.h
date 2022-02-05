#pragma once

#include <chrono>
#include <iostream>
#include <vector>

#include "../core/test.h"

// How to use:
// BENCHMARK(Foo) {
//   code_to_be_measured();
// }
//
// Will only be evaluted if RunAllBenchmarks() is called.

void RunAllBenchmarks();

#define BENCHMARK(name)                                                        \
  struct BenchmarkOp##name {                                                   \
    void operator()();                                                         \
  };                                                                           \
  internal::Benchmark<BenchmarkOp##name> bm_instance##name(#name);             \
  void BenchmarkOp##name::operator()()

namespace internal {

class BenchmarkBase {
public:
  virtual void Run() const = 0;

protected:
  BenchmarkBase();
};

class BenchmarkRegistration {
public:
  void Register(BenchmarkBase *b) { benchmarks_.push_back(b); }

  void RunAll() {
    for (const auto *benchmark : benchmarks_) {
      benchmark->Run();
    }
  }

  static BenchmarkRegistration &Singleton() {
    static BenchmarkRegistration *kSingleton = new BenchmarkRegistration();
    return *kSingleton;
  }

private:
  std::vector<BenchmarkBase *> benchmarks_;
};

BenchmarkBase::BenchmarkBase() {
  BenchmarkRegistration::Singleton().Register(this);
}

// Converts a duration to a 3 decimal double with a given readable unit.
std::pair<double, std::string_view>
GetGoodUnit(std::chrono::duration<double, std::nano> duration) {
  double t = 0;
  std::string_view unit = "";
  if (duration < std::chrono::nanoseconds(1000)) {
    t = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    unit = "ns";
  } else if (duration < std::chrono::microseconds(1000)) {
    t = 0.001 *
        std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
    unit = "us";
  } else if (duration < std::chrono::milliseconds(1000)) {
    t = 0.001 *
        std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    unit = "ms";
  } else {
    t = 0.001 *
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    unit = "s";
  }
  return {t, unit};
}

template <typename Op> class Benchmark : public BenchmarkBase {
public:
  Benchmark(std::string_view name) : name_(name) {}
  void Run() const final { ExecuteBenchmark(); }

private:
  // Using a templated Functor here instead of indirection avoids a virtual call
  // in each iteration, which makes the benchmark more accurate.
  void ExecuteBenchmark() const {
    std::cout << "Benchmark " << name_ << std::endl;
    Op op;
    const std::chrono::duration wanted_total = std::chrono::seconds(1);
    constexpr int kEstimateIterations = 50;

    const std::chrono::steady_clock::time_point begin =
        std::chrono::steady_clock::now();

    for (int r = 0; r < kEstimateIterations; ++r) {
      op();
    }
    const std::chrono::steady_clock::time_point estimate_end =
        std::chrono::steady_clock::now();
    const std::chrono::duration estimate_duration = estimate_end - begin;
    const std::chrono::duration single_run =
        estimate_duration / kEstimateIterations;

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

    auto [t, unit] = GetGoodUnit(per_run_total);
    // std::chrono::duration_cast<std::chrono::nanoseconds>()
    //     .count());
    std::cout << "Run average time per iteration: " << t << " " << unit
              << std::endl
              << std::endl;
  }

  std::string_view name_;
};

} // namespace internal

void RunAllBenchmarks() {
  internal::BenchmarkRegistration::Singleton().RunAll();
}

TEST(GetGoodUnitNanos) {
  auto [t, unit] = internal::GetGoodUnit(std::chrono::nanoseconds(5));
  EXPECT_NEAR(t, 5);
  EXPECT_EQ(unit, "ns");
}

TEST(GetGoodUnitMicros) {
  auto [t, unit] = internal::GetGoodUnit(std::chrono::nanoseconds(5500));
  EXPECT_NEAR(t, 5.5);
  EXPECT_EQ(unit, "us");
}

TEST(GetGoodUnitMillis) {
  auto [t, unit] = internal::GetGoodUnit(std::chrono::microseconds(5500));
  EXPECT_NEAR(t, 5.5);
  EXPECT_EQ(unit, "ms");
}

TEST(GetGoodUnitSeconds) {
  auto [t, unit] = internal::GetGoodUnit(std::chrono::milliseconds(5500));
  EXPECT_NEAR(t, 5.5);
  EXPECT_EQ(unit, "s");
}
