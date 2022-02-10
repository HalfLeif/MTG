#pragma once

#include <algorithm>
#include <mutex>
#include <random>
#include <vector>

#include "test.h"

class MutexLock {
public:
  MutexLock(std::mutex *mutex) : mutex_(mutex) { mutex_->lock(); }
  ~MutexLock() { mutex_->unlock(); }

private:
  std::mutex *mutex_;
};

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
