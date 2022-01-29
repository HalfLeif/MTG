#pragma once

#include <iostream>

extern const bool DEBUG_ON;
extern const bool PARANOIA;

#define ERROR (std::cerr << "Error at " << __FILE__ << ":" << __LINE__ << " : ")
#define INFO                                                                   \
  if (DEBUG_ON)                                                                \
  (std::cout << __FILE__ << ":" << __LINE__ << " : ")

class FatalLog {
public:
  ~FatalLog() { std::exit(1); }

  template <typename T> std::ostream &operator<<(const T &arg) const {
    return std::cerr << arg;
  }
};

#define FATAL                                                                  \
  (FatalLog() << "Fatal error at " << __FILE__ << ":" << __LINE__ << " : ")

#define CHECK(a)                                                               \
  if (!(a))                                                                    \
  (FatalLog() << "Check failed: " << #a << " at " << __FILE__ << ":"           \
              << __LINE__ << std::endl)
