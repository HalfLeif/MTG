#pragma once

extern const bool DEBUG_ON;
extern const bool PARANOIA;

#define ERROR (std::cerr << "Error at " << __FILE__ << ":" << __LINE__ << " : ")
#define INFO                                                                   \
  if (DEBUG_ON)                                                                \
  (std::cout << __FILE__ << ":" << __LINE__ << " : ")
