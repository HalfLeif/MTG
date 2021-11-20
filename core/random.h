#include <algorithm>
#include <mutex>
#include <random>
#include <vector>

class MutexLock {
public:
  MutexLock(std::mutex *mutex) : mutex_(mutex) { mutex_->lock(); }
  ~MutexLock() { mutex_->unlock(); }

private:
  std::mutex *mutex_;
};

class ThreadsafeRandom {
public:
  ThreadsafeRandom() : g_(rd_()) {}

  unsigned int Rand() {
    MutexLock lock(&mutex_);
    return rd_();
  }

  // Returns a double between [0, 1).
  double RandOne() {
    constexpr int kMax = 100000000;
    return static_cast<double>(Rand() % kMax) / static_cast<double>(kMax);
  }

  template <typename T> void Shuffle(std::vector<T> &vec) {
    MutexLock lock(&mutex_);
    std::shuffle(vec.begin(), vec.end(), g_);
  }

private:
  std::random_device rd_;
  std::mt19937 g_;
  std::mutex mutex_;
};