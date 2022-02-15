#pragma once

#include "library.h"

struct Param {
  const Library *lib;
  Experiment experiment = Experiment::base;
  int primary = 0;
  int secondary = 0;
  int ternary = 0;
  DeckSize deck_size = DeckSize::limited;
};

std::ostream &operator<<(std::ostream &stream, const Param &param) {
  stream << "Param experiment: " << param.experiment;
  // Note: This is an approximation since must also take into account number of
  // non-basic lands! For a complete overview, should print lands directly
  // instead of printing the params.
  stream << "  " << param.lib->PrimaryColor() << "=" << param.primary;
  if (param.secondary > 0) {
    stream << "  " << param.lib->SecondaryColor() << "=" << param.secondary;
  }
  if (param.ternary > 0) {
    stream << "  " << param.lib->TernaryColor() << "=" << param.ternary;
  }
  return stream;
}
