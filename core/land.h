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
  Color color;
  std::optional<Color> secondary = std::nullopt;

  bool operator==(const Land &other) const {
    if (type != other.type) {
      return false;
    }
    switch (type) {
    case LandType::basic:
      return color == other.color;
    case LandType::dual: {
      std::pair<Color, Color> left = {color, *secondary};
      std::pair<Color, Color> right = {other.color, *other.secondary};
      std::pair<Color, Color> right_inv = {*other.secondary, other.color};
      return (left == right) || (left == right_inv);
    }
    case LandType::fetch:
    case LandType::shore:
      // Always true if is same type.
      return true;
    }
    return true;
  }
};

Land BasicLand(Color c) {
  return {
      .type = LandType::basic,
      .color = c,
  };
}

Land DualLand(Color c, Color secondary) {
  return {
      .type = LandType::dual,
      .color = c,
      .secondary = secondary,
  };
}

Land FetchLand() {
  return {
      .type = LandType::fetch,
      .color = Color::Colorless,
  };
}

Land Shore() {
  return {
      .type = LandType::shore,
      .color = Color::Colorless,
  };
}

bool IsBasicLand(const Land &land) { return land.type == LandType::basic; }
bool IsSwamp(const Land &land) {
  return IsBasicLand(land) && land.color == Color::Black;
}
bool IsPlains(const Land &land) {
  return IsBasicLand(land) && land.color == Color::White;
}
bool IsFetchLand(const Land &land) { return land.type == LandType::fetch; }

std::string ToString(const Land &land) {
  std::string result;
  switch (land.type) {
  case LandType::basic:
    return ToString(land.color);
  case LandType::dual:
    return ToString(land.color) + ToString(*land.secondary);
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
