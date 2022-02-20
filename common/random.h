#pragma once

#include <algorithm>
#include <random>
#include <vector>

#include "mutex_lock.h"
#include "test.h"

class ThreadsafeRandom {
public:
  ThreadsafeRandom() : ThreadsafeRandom(1234) {}
  ThreadsafeRandom(int seed) : generator_(seed) {}

  unsigned int Rand() {
    MutexLock lock(&mutex_);
    return generator_();
  }

  // Returns a double between [0, 1).
  double RandOne() {
    // Use a power of two to make modulo and division somewhat more efficient.
    constexpr int kMax = 1 << 24;
    return static_cast<double>(Rand() % kMax) / static_cast<double>(kMax);
  }

  // Shuffles an entire vector.
  template <typename T> void Shuffle(std::vector<T> &vec) {
    MutexLock lock(&mutex_);
    std::shuffle(vec.begin(), vec.end(), generator_);
  }

  // Shuffles a section of a vector.
  template <typename T> void Shuffle(std::vector<T> &vec, int begin, int end) {
    MutexLock lock(&mutex_);
    std::shuffle(vec.begin() + begin, vec.begin() + end, generator_);
  }

private:
  std::mt19937 generator_;
  std::mutex mutex_;
};

// Returns the position of the sampled item, not pair.second.
// Could use binary search if cumulative distribution and sampled with
// repetition. However, sampling without repetition doesn't benefit from it.
template <typename T>
int SampleOne(const std::vector<std::pair<double, T>> &distribution, double r,
              double total) {
  // By default picks last element. Should never be necessary when total is
  // correct.
  int pos = distribution.size() - 1;
  double acc = 0;
  const double target = r * total;
  for (int i = 0; i < distribution.size(); ++i) {
    acc += distribution[i].first;
    if (target < acc) {
      pos = i;
      break;
    }
  }
  return pos;
}

// -----------------------------------------------------------------------------

TEST(RandomSameSeedProducesSameResult) {
  ThreadsafeRandom r1(1234);
  ThreadsafeRandom r2(1234);
  EXPECT_EQ(r1.Rand(), r2.Rand());
  EXPECT_EQ(r1.Rand(), r2.Rand());
}

TEST(RandomDifferentSeedsProducesDifferentResult) {
  ThreadsafeRandom r1(1);
  ThreadsafeRandom r2(2);
  EXPECT_NE(r1.Rand(), r2.Rand());
  EXPECT_NE(r1.Rand(), r2.Rand());
}

TEST(RandOneAlwaysWithinRange) {
  ThreadsafeRandom rand(1234);
  for (int i = 0; i < 100; ++i) {
    double r = rand.RandOne();
    EXPECT_LT(r, 1.0);
    EXPECT_LT(0.0, r);
  }
}

TEST(SampleOneOnlyOneChoice) {
  std::vector<std::pair<double, std::string>> distribution;
  distribution.emplace_back(0, "Bad");
  distribution.emplace_back(0, "Bad2");
  distribution.emplace_back(25, "Good");

  int sample = SampleOne(distribution, 0.1, 25);
  EXPECT_EQ(sample, 2);
  EXPECT_EQ(distribution[sample].second, "Good");
}

TEST(SampleOneReturnsCorrect) {
  std::vector<std::pair<double, std::string>> distribution;
  distribution.emplace_back(1, "Small");
  distribution.emplace_back(1, "Medium");
  distribution.emplace_back(1, "Big");

  EXPECT_EQ(distribution[SampleOne(distribution, 0.1, 3)].second, "Small");
  EXPECT_EQ(distribution[SampleOne(distribution, 0.4, 3)].second, "Medium");
  EXPECT_EQ(distribution[SampleOne(distribution, 0.8, 3)].second, "Big");
  EXPECT_EQ(distribution[SampleOne(distribution, 1.001, 3)].second, "Big");
}
