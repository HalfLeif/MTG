#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "../common/debug.h"
#include "../common/test.h"
#include "../core/spell.h"

std::vector<std::string_view> SplitLine(std::string_view line,
                                        std::string_view delimiter) {
  std::vector<std::string_view> result;
  for (size_t pos = 0; pos < line.size();) {
    size_t next = line.find(delimiter, pos);
    if (next == std::string_view::npos) {
      next = line.size();
    }
    const size_t length = next - pos;
    result.push_back(line.substr(pos, length));
    pos = next + delimiter.size();
  }
  return result;
}

char TypeToPriority(std::string_view type) {
  // Reducing priority for Instants and Sorceries make good removals count as
  // bad spells, because they have low priority and then are rarely played. In
  // reality, removals are terrific. Hence, should have same priority as
  // Creatures. if (type == "Instant" || type == "Sorcery") {
  //   return 0;
  // }
  return 1;
}

constexpr double kMaxBoost = 0.50;
constexpr double kMinBoost = -0.30;
constexpr double kMaxOrder = 260;

double BonusFromOrder(int draft_order, int spell_cost) {
  double relative_bonus =
      kMaxBoost + draft_order * (kMinBoost - kMaxBoost) / kMaxOrder;
  return relative_bonus * spell_cost;
}

Spell ParseLine(const std::string_view line) {
  // Note: Doesn't handle csv escaping atm. For now might not be needed.
  Spell spell;
  std::vector<std::string_view> fields = SplitLine(line, ";");
  if (fields.size() >= 4) {
    // mana;name;type;order
    spell.cost = ParseMana(fields[0]);
    spell.name = fields[1];
    spell.priority = TypeToPriority(fields[2]);
    spell.point_bonus =
        BonusFromOrder(std::atoi(fields[3].data()), spell.cost[Color::Total]);
  } else {
    ERROR << "Failed to parse '" << line << "'\n";
  }

  return spell;
}

std::vector<Spell> ReadCards(std::string fname) {
  // Note: Does not read any lands. Currently filter to only non-lands at python
  // export time.
  std::vector<Spell> spells;
  std::ifstream csv;
  csv.open(fname, std::ios::in);
  if (csv.is_open()) {
    std::string line;
    bool header = true;
    while (std::getline(csv, line)) {
      if (header) {
        // First row is just the csv header.
        header = false;
        continue;
      }
      spells.push_back(ParseLine(line));
    }
  } else {
    ERROR << "Failed to open " << fname;
  }
  csv.close();
  INFO << "Parsed " << spells.size() << " cards from " << fname << std::endl;
  return spells;
}

// -----------------------------------------------------------------------------

TEST(SplitLine) {
  // std::vector<std::string_view> fields;
  std::vector<std::string_view> fields =
      SplitLine("W;Blessed Defiance;Instant;237", ";");
  EXPECT_EQ(fields.size(), 4);
  if (fields.size() >= 4) {
    EXPECT_EQ(fields[0], "W");
    EXPECT_EQ(fields[1], "Blessed Defiance");
    EXPECT_EQ(fields[2], "Instant");
    EXPECT_EQ(fields[3], "237");
  }
}

TEST(BonusFromOrder) {
  EXPECT_NEAR(BonusFromOrder(0, 1), kMaxBoost);
  EXPECT_NEAR(BonusFromOrder(260, 1), kMinBoost);

  double normal = BonusFromOrder(150, 1);
  EXPECT_LT(-0.10, normal);
  EXPECT_LT(normal, 0.10);
}

TEST(BonusFromOrderScalesWithMana) {
  double good = BonusFromOrder(2, 4);
  EXPECT_LT(0, good);
  EXPECT_LT(good, kMaxBoost * 4);

  double bad = BonusFromOrder(230, 4);
  EXPECT_LT(kMinBoost * 4, bad);
  EXPECT_LT(bad, 0);
}
