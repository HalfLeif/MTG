#pragma once

#include <mutex>

class MutexLock {
public:
  MutexLock(std::mutex *mutex) : mutex_(mutex) { mutex_->lock(); }
  ~MutexLock() { mutex_->unlock(); }

private:
  std::mutex *mutex_;
};
