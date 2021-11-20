#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "../core/debug.h"
#include "../core/spell.h"
#include "../core/test.h"

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
  if (type == "Instant" || type == "Sorcery") {
    return 0;
  }
  return 1;
}

double BonusFromOrder(int draft_order) {
  // TODO compute actual bonus!
  return 0.0;
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
    spell.point_bonus = BonusFromOrder(std::atoi(fields[3].data()));
  } else {
    ERROR << "Failed to parse '" << line << "'\n";
  }

  return spell;
}

std::vector<Spell> ReadCards() {
  // Note: Does not read any lands. Currently filter to only non-lands at python
  // export time.
  std::vector<Spell> spells;
  std::string fname = "data/mid/cards.csv";
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
