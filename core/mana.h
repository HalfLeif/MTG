#pragma once

#include <cstdint>
#include <iostream>
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
    Iter(size_t pos, const std::array<int, kEnd> *arr) : pos_(pos), arr_(arr) {}

    inline mapped_type value() const { return (*arr_)[pos_]; }

    std::pair<key_type, mapped_type> operator*() const {
      const Color color = static_cast<Color>(pos_);
      return {color, value()};
    }

    bool operator==(const Iter &other) const {
      return pos_ == other.pos_ && arr_ == other.arr_;
    }
    bool operator!=(const Iter &other) const { return !(*this == other); }

    // Increments iterator to next valid position or kEnd.
    void operator++() {
      ++pos_;
      // Must skip empty values on iteration.
      while (pos_ < kEnd && value() <= 0) {
        ++pos_;
      }
    }

  private:
    size_t pos_;
    const std::array<int, kEnd> *arr_ = nullptr;
  };

  mapped_type FindValue(Color key) const {
    CHECK(key < Color::ENUM_SIZE);
    size_t pos = static_cast<size_t>(key);
    return cost_[pos];
  }

  bool contains(Color key) const { return FindValue(key) > 0; }

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
      // TODO: use actual X mana.
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
  int total_mana = 0;
  for (auto [color, value] : mana) {
    if (color == Color::Total) {
      total_mana = value;
      continue;
    }
    color_mana_sum += value;
    std::string color_str = ToString(color);
    for (int i = 0; i < value; ++i) {
      result.append(color_str);
    }
  }
  int colorless_mana = total_mana - color_mana_sum;
  CHECK(colorless_mana >= 0)
      << "Total mana " << total_mana << " vs " << color_mana_sum;
  if (colorless_mana > 0) {
    result.append(std::to_string(colorless_mana));
  }

  return result;
}

std::ostream &operator<<(std::ostream &stream, const ManaCost &mana) {
  return stream << ToString(mana);
}

// -----------------------------------------------------------------------------

TEST(ParseManaSimple) {
  EXPECT_EQ(ToString(ParseMana("B3")), "B3");
  EXPECT_EQ(ToString(ParseMana("BB")), "BB");
  EXPECT_EQ(ToString(ParseMana("BBG2")), "BBG2");
}

TEST(ManaAddition) {
  ManaCost a = ParseMana("BB1");
  ManaCost b = ParseMana("R3");
  a += b;
  EXPECT_EQ(ToString(a), "BBR4");
}
