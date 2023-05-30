#pragma once

#include <sstream>
#include <string>

#include "library.h"

struct Param {
  const Library *lib;
  Experiment experiment = Experiment::base;
  int primary = 0;
  int secondary = 0;
  int tertiary = 0;
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
  if (param.tertiary > 0) {
    stream << "  " << param.lib->TertiaryColor() << "=" << param.tertiary;
  }
  return stream;
}

std::string ToString(const Param &param) {
  std::ostringstream ostream;
  ostream << param;
  return ostream.str();
}

TEST(ParamToString) {
  Library lib = Library::Builder()
                    .AddSpell(MakeSpell("B2"))
                    .AddSpell(MakeSpell("B2"))
                    .AddSpell(MakeSpell("B2"))
                    .AddSpell(MakeSpell("W3"))
                    .AddSpell(MakeSpell("W3"))
                    .AddSpell(MakeSpell("G5"))
                    .Build();
  Param param = {
      .lib = &lib,
      .primary = 8,
      .secondary = 7,
      .tertiary = 2,
  };
  EXPECT_EQ(ToString(param), "Param experiment: base  B=8  W=7  G=2");
}
