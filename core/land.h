#pragma once

#include <optional>

#include "mana.h"

enum class LandType {
  basic,
  dual,
  fetch,
  shore,
};

struct Land {
  LandType type;
  ManaCost colors;

  // E.g. 0.5 for gaining one life.
  double bonus = 0.0;
  // Color color;
  // std::optional<Color> secondary = std::nullopt;

  bool operator==(const Land &other) const {
    if (type != other.type) {
      return false;
    }
    switch (type) {
    case LandType::basic:;
    case LandType::dual:
      return colors == other.colors;
    case LandType::fetch:
    case LandType::shore:
      // Always true if is same type.
      return true;
    }
    return true;
  }
};

Land TapLand(std::string_view mana) {
  ManaCost colors = ParseMana(mana);
  colors[Color::Total] = 1;
  return {
      .type = LandType::dual,
      .colors = colors,
  };
}

Land BasicLand(Color c) {
  ManaCost colors;
  colors[c]++;
  colors[Color::Total]++;
  return {
      .type = LandType::basic,
      .colors = colors,
  };
}

Land DualLand(Color c, Color secondary) {
  ManaCost colors;
  colors[c]++;
  colors[secondary]++;
  colors[Color::Total]++;
  return {
      .type = LandType::dual,
      .colors = colors,
  };
}

Land DualLand(std::string_view basic_land_colors) {
  ManaCost colors = ParseMana(basic_land_colors);
  colors[Color::Total] = 1;
  return {
      .type = LandType::dual,
      .colors = colors,
  };
}

// Empty means any color.
Land FetchLand(double bonus = 0.0, std::string_view basic_land_colors = "") {
  return Land{
      .type = LandType::fetch,
      .colors = ParseMana(basic_land_colors),
      .bonus = bonus,
  };
}

Land Shore() {
  ManaCost colors;
  colors[Color::Colorless]++;
  colors[Color::Total]++;
  return {
      .type = LandType::shore,
      .colors = colors,
  };
}

inline bool IsBasicLand(const Land &land) {
  return land.type == LandType::basic;
}
bool IsSwamp(const Land &land) {
  return IsBasicLand(land) && land.colors.contains(Color::Black);
}
bool IsPlains(const Land &land) {
  return IsBasicLand(land) && land.colors.contains(Color::White);
}
bool IsMountain(const Land &land) {
  return IsBasicLand(land) && land.colors.contains(Color::Red);
}
bool IsFetchLand(const Land &land) { return land.type == LandType::fetch; }

std::string ToString(const Land &land) {
  std::string result;
  switch (land.type) {
  case LandType::basic:
  case LandType::dual:
    return ToString(land.colors);
  case LandType::fetch:
    return "Fetch";
  case LandType::shore:
    return "Shore";
  }
  ERROR << "Unknown LandType: " << static_cast<int>(land.type);
  return "LAND?";
}

std::ostream &operator<<(std::ostream &stream, const Land &land) {
  return stream << ToString(land);
}
