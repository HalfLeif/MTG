#pragma once

#include <cstdint>
#include <iostream>
#include <map>
#include <string_view>

#include "../common/container.h"
#include "../common/debug.h"
#include "../common/test.h"

enum class Color : int8_t {
  Total = 0, // Total converted mana cost (including Grey).
  White,
  Blue,
  Black,
  Red,
  Green,
  Colorless,
  ENUM_SIZE,
};

// Represent mana pool as how much mana could be spent per color!
// And then compare mana spent vs total mana pool. Very similar to MaxFlow
// problem. Edge case: dual W/B land + G land cannot pay for WB. Although this
// case should be rare (maybe OK for simulation purposes?).
class ManaCost {
public:
  ManaCost() { cost_.fill(0); }

  using key_type = Color;
  using mapped_type = int;
  static constexpr size_t kEnd = static_cast<size_t>(Color::ENUM_SIZE);

  class Iter {
  public:
    // Finds the next valid position after this position.
    Iter(size_t pos, const std::array<int, kEnd> *arr) : pos_(pos), arr_(arr) {
      FindValidPosition();
    }

    inline key_type key() const { return static_cast<key_type>(pos_); };

    inline mapped_type value() const { return (*arr_)[pos_]; }

    std::pair<key_type, mapped_type> operator*() const {
      return {key(), value()};
    }

    bool operator==(const Iter &other) const {
      return pos_ == other.pos_ && arr_ == other.arr_;
    }
    bool operator!=(const Iter &other) const { return !(*this == other); }

    // Increments iterator to next valid position or kEnd.
    void operator++() {
      ++pos_;
      FindValidPosition();
    }

  private:
    // If not already at a valid position, then will move to the next valid
    // position or end().
    void FindValidPosition() {
      while (pos_ < kEnd && value() <= 0) {
        ++pos_;
      }
    }
    size_t pos_;
    const std::array<int, kEnd> *arr_ = nullptr;
  };

  // Total amount of mana.
  mapped_type Total() const {
    size_t pos = static_cast<size_t>(Color::Total);
    return cost_[pos];
  }

  mapped_type FindValue(Color key) const {
    CHECK(key < Color::ENUM_SIZE);
    size_t pos = static_cast<size_t>(key);
    return cost_[pos];
  }

  bool contains(Color key) const { return FindValue(key) > 0; }
  bool empty() const { return begin() == end(); }

  Iter begin() const { return make_iter(static_cast<Color>(0)); }
  Iter end() const { return make_iter(Color::ENUM_SIZE); }
  // find() is suboptimal since creates iterators.
  // Calling FindValue directly is more efficient.

  mapped_type &operator[](const key_type &key) {
    CHECK(key < Color::ENUM_SIZE);
    const size_t pos = static_cast<size_t>(key);
    return cost_[pos];
  }

  ManaCost &operator+=(const ManaCost &other) {
    for (size_t i = 0; i < kEnd; ++i) {
      cost_[i] += other.cost_[i];
    }
    return *this;
  }

  bool operator==(const ManaCost &other) const { return cost_ == other.cost_; }

  bool operator!=(const ManaCost &other) const { return !(*this == other); }

  bool operator<(const ManaCost &other) const {
    if (this->Total() != other.Total()) {
      return this->Total() < other.Total();
    }
    auto i = this->begin();
    auto j = other.begin();
    for (; i != this->end() && j != other.end(); ++i, ++j) {
      if (i.key() != j.key()) {
        return i.key() < j.key();
      }
    }
    if (i == this->end() && j != other.end()) {
      // left side finished, but right side did not.
      // hence left has more types of color.
      return true;
    }
    return false;
  }

  // Unique colors
  ManaCost GetColors() const {
    size_t count = 0;
    ManaCost colors;
    for (auto [color, value] : *this) {
      if (color != Color::Total && color != Color::Colorless) {
        ++count;
        colors[color] = 1;
      }
    }
    colors[Color::Total] = count;
    return colors;
  }

private:
  Iter make_iter(key_type key) const {
    CHECK(key <= Color::ENUM_SIZE);
    return Iter(static_cast<size_t>(key), &cost_);
  }

  // Consider 0 values to not be present.
  std::array<int, kEnd> cost_;
};

void AddUniversalColor(ManaCost *mana_pool) {
  ++(*mana_pool)[Color::White];
  ++(*mana_pool)[Color::Blue];
  ++(*mana_pool)[Color::Black];
  ++(*mana_pool)[Color::Red];
  ++(*mana_pool)[Color::Green];
}

void UpdateMaxColors(ManaCost &mana_needs, const ManaCost &spell_needs) {
  for (const auto [color, amount] : spell_needs) {
    mana_needs[color] = std::max(mana_needs[color], amount);
  }
}

int TotalCost(const ManaCost &cost) { return cost.FindValue(Color::Total); }

ManaCost ParseMana(std::string_view mana) {
  ManaCost cost;
  for (char c : mana) {
    if (c >= '0' && c <= '9') {
      char amount = c - '0';
      cost[Color::Total] += amount;
    } else if (c == 'W') {
      ++cost[Color::White];
      ++cost[Color::Total];
    } else if (c == 'U') {
      ++cost[Color::Blue];
      ++cost[Color::Total];
    } else if (c == 'B') {
      ++cost[Color::Black];
      ++cost[Color::Total];
    } else if (c == 'R') {
      ++cost[Color::Red];
      ++cost[Color::Total];
    } else if (c == 'G') {
      ++cost[Color::Green];
      ++cost[Color::Total];
    } else if (c == 'X') {
      cost[Color::Total] += 2;
    } else {
      ERROR << "Unrecognized char when parsing mana: " << c << " (" << int(c)
            << ")\n";
    }
  }
  return cost;
}

std::string ToString(Color color) {
  switch (color) {
  case Color::Total:
  case Color::ENUM_SIZE:
    return "";
  case Color::White:
    return "W";
  case Color::Blue:
    return "U";
  case Color::Black:
    return "B";
  case Color::Red:
    return "R";
  case Color::Green:
    return "G";
  case Color::Colorless:
    return "C";
  }
  FATAL << "Unknown color: " << static_cast<int>(color);
  return "?";
}

std::ostream &operator<<(std::ostream &stream, Color color) {
  return stream << ToString(color);
}

std::string ToString(const ManaCost &mana) {
  std::string result = "";
  int color_mana_sum = 0;
  const int total_mana = mana.Total();
  for (auto [color, value] : mana) {
    if (color == Color::Total) {
      continue;
    }
    color_mana_sum += value;
    std::string color_str = ToString(color);
    for (int i = 0; i < value; ++i) {
      result.append(color_str);
    }
  }
  int colorless_mana = total_mana - color_mana_sum;
  // Note: mana can have more color than total for e.g. dual lands.
  if (colorless_mana > 0) {
    result.append(std::to_string(colorless_mana));
  }

  return result;
}

std::ostream &operator<<(std::ostream &stream, const ManaCost &mana) {
  return stream << ToString(mana);
}

void RecursivelyAddColors(const std::vector<Color> &colors, int elem,
                          int min_different, int max_different, ManaCost mana,
                          std::vector<ManaCost> *output) {
  if (elem >= 0 && elem >= colors.size()) {
    return;
  }
  if (mana.Total() >= max_different) {
    // Sufficient number of colors already.
    return;
  }

  if (elem >= 0) {
    ++mana[colors[elem]];
    ++mana[Color::Total];
    if (mana.Total() >= min_different) {
      output->push_back(mana);
    }
  }

  for (int i = elem + 1; i < colors.size(); ++i) {
    // Kick off N+1 colors.
    // Intentionally copies mana so that modifications only affect sub tree.
    RecursivelyAddColors(colors, i, min_different, max_different, mana, output);
  }
}

// Generates all non-empty color combinations with at most `max_different`
// distinct colors.
void GenerateAllColorCombinations(const std::vector<Color> &colors,
                                  int min_different, int max_different,
                                  std::vector<ManaCost> *output) {
  // Start with -1 in order to kick of all colors.
  RecursivelyAddColors(colors, -1, min_different, max_different, ManaCost(),
                       output);
}

// -----------------------------------------------------------------------------

TEST(ManaIteratorBeginEqualsEndWhenEmpty) {
  ManaCost mana;
  EXPECT_TRUE(mana.empty());
  EXPECT_TRUE(mana.begin() == mana.end());
}

TEST(ManaIteratorLoop) {
  ManaCost mana = ParseMana("RRRR");
  int count = 0;
  for (auto it : mana) {
    count++;
  }
  // One for Red and one for Total.
  EXPECT_EQ(count, 2);
}

TEST(ParseManaSimple) {
  EXPECT_EQ(ToString(ParseMana("B3")), "B3");
  EXPECT_EQ(ToString(ParseMana("BB")), "BB");
  EXPECT_EQ(ToString(ParseMana("BBG2")), "BBG2");
}

TEST(ManaCostEq) {
  EXPECT_EQ(ParseMana("B3"), ParseMana("B3"));
  EXPECT_NE(ParseMana("W3"), ParseMana("B3"));
}

TEST(ManaAddition) {
  ManaCost a = ParseMana("BB1");
  ManaCost b = ParseMana("R3");
  a += b;
  EXPECT_EQ(ToString(a), "BBR4");
}

TEST(RecursivelyAddColors) {
  std::vector<ManaCost> combinations;
  GenerateAllColorCombinations({Color::Black, Color::White}, 1, 3,
                               &combinations);
  EXPECT_EQ(combinations.size(), 3);

  std::set<std::string> mana_readable;
  for (ManaCost cost : combinations) {
    mana_readable.insert(ToString(cost));
  }
  EXPECT_TRUE(ContainsKey(mana_readable, "B"));
  EXPECT_TRUE(ContainsKey(mana_readable, "W"));
  EXPECT_TRUE(ContainsKey(mana_readable, "WB"));
}

TEST(RecursivelyAddColorsMinMaxDifferent) {
  std::vector<ManaCost> combinations;
  GenerateAllColorCombinations(
      {Color::Black, Color::White, Color::Blue, Color::Green, Color::Red}, 2, 2,
      &combinations);
  EXPECT_EQ(combinations.size(), 10);

  std::set<std::string> mana_readable;
  for (ManaCost cost : combinations) {
    mana_readable.insert(ToString(cost));
  }
  // No monocolor
  EXPECT_FALSE(ContainsKey(mana_readable, "B"));
  EXPECT_FALSE(ContainsKey(mana_readable, "W"));
  EXPECT_FALSE(ContainsKey(mana_readable, "G"));

  // Only dual color
  EXPECT_TRUE(ContainsKey(mana_readable, "WB"));
  EXPECT_TRUE(ContainsKey(mana_readable, "BR"));
  EXPECT_TRUE(ContainsKey(mana_readable, "RG"));

  EXPECT_FALSE(ContainsKey(mana_readable, "WBR"));
}

TEST(ManaCostLessThanPrioritizesSize) {
  EXPECT_LT(ParseMana("R1"), ParseMana("R3"));
  EXPECT_LT(ParseMana("R1"), ParseMana("W3"));
  EXPECT_LT(ParseMana("BR"), ParseMana("WBR"));
}

TEST(ManaCostLessThanIdentity) {
  EXPECT_FALSE(ParseMana("W") < ParseMana("W"));
}

TEST(ManaCostLessThanRespectsColor) {
  EXPECT_LT(ParseMana("1"), ParseMana("W"));
  EXPECT_LT(ParseMana("W"), ParseMana("U"));
  EXPECT_LT(ParseMana("U"), ParseMana("B"));
  EXPECT_LT(ParseMana("B"), ParseMana("R"));
  EXPECT_LT(ParseMana("R"), ParseMana("G"));

  EXPECT_FALSE(ParseMana("W") < ParseMana("1"));
  EXPECT_FALSE(ParseMana("U") < ParseMana("W"));
  EXPECT_FALSE(ParseMana("B") < ParseMana("U"));
  EXPECT_FALSE(ParseMana("R") < ParseMana("B"));
  EXPECT_FALSE(ParseMana("G") < ParseMana("R"));
}

TEST(ManaCostLessThanRespectsMulticolor) {
  EXPECT_LT(ParseMana("WU"), ParseMana("UB"));
  EXPECT_LT(ParseMana("UB"), ParseMana("UR"));
  EXPECT_LT(ParseMana("BR"), ParseMana("RG"));
  EXPECT_LT(ParseMana("WG"), ParseMana("BR"));
  EXPECT_LT(ParseMana("WUG"), ParseMana("BRG"));

  EXPECT_FALSE(ParseMana("UB") < ParseMana("WU"));
  EXPECT_FALSE(ParseMana("UR") < ParseMana("UB"));
  EXPECT_FALSE(ParseMana("RG") < ParseMana("BR"));
  EXPECT_FALSE(ParseMana("BR") < ParseMana("WG"));
  EXPECT_FALSE(ParseMana("BRG") < ParseMana("WUG"));
}

TEST(ManaCostNumColors) {
  EXPECT_EQ(ParseMana("3").GetColors(), ParseMana(""));
  EXPECT_EQ(ParseMana("W1").GetColors(), ParseMana("W"));
  EXPECT_EQ(ParseMana("WWW").GetColors(), ParseMana("W"));
  EXPECT_EQ(ParseMana("WWU").GetColors(), ParseMana("WU"));
  EXPECT_EQ(ParseMana("BRG1").GetColors(), ParseMana("BRG"));
}

TEST(ManaCostSet) {
  ManaCost w1 = ParseMana("W1").GetColors();
  ManaCost w2 = ParseMana("W2").GetColors();
  EXPECT_EQ(w1, w2);
  EXPECT_FALSE(w1 < w2);
  EXPECT_FALSE(w2 < w1);

  std::map<ManaCost, int> map;
  map[w1] = 5;
  EXPECT_EQ(map[w1], 5);
  EXPECT_EQ(map[w2], 5);
}
