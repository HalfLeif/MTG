#pragma once

#include "card_logic.h"
#include "collection.h"
#include "library.h"
#include "test.h"

struct TurnState {
  ManaCost mana_pool;
  ManaCost agg_spell_cost;
};

void DrawOne(Player *player) {
  auto &lib = player->library;
  int total_cards = lib.spells.size() + lib.lands.size();
  if (total_cards <= 0) {
    ERROR << "Cannot draw card because the library is empty!\n";
    return;
  }
  int picked = rand() % total_cards;
  // INFO << "Rand pick " << picked << "\n";
  if (picked >= lib.spells.size()) {
    // Picked a land
    picked -= lib.spells.size();
    Land *land = MoveLand(picked, player->library, player->hand);
    INFO << "Drew " << *land << "\n";
  } else {
    // Picked a non-land
    Spell *spell = MoveSpell(picked, player->library, player->hand);
    INFO << "Drew " << *spell << "\n";
  }
}

void DrawN(Player *player, int n) {
  for (int i = 0; i < n; ++i) {
    DrawOne(player);
  }
}

void TapLand(const Land &land, ManaCost &mana_pool) {
  if (land.type == LandType::fetch) {
    ERROR << "Attempted to tap a fetch land for mana!\n";
    std::exit(1);
    return;
  }
  ++mana_pool[land.color];
  ++mana_pool[Color::Total];
  if (land.secondary.has_value()) {
    ++mana_pool[*land.secondary];
  }
}

bool IsColorStarved(const Library &lib, const ManaCost &mana_pool) {
  if (FindWithDefault(mana_pool, lib.PrimaryColor(), 0) < 1) {
    return true;
  }
  if (FindWithDefault(mana_pool, lib.SecondaryColor(), 0) < 1) {
    return true;
  }
  return false;
}

void ProduceMana(const Library &lib, const Deck &battlefield,
                 ManaCost *mana_pool) {
  auto &lands = battlefield.lands;
  int shores = 0;
  for (int i = 0; i < lands.size(); ++i) {
    if (lands[i].type == LandType::fetch) {
      // Fetch lands are used when played, so should never be tapped during this
      // step!
      // However, this situation can occur when estimating mana in the hand...
      // ERROR << "Attempted to tap a fetch land for mana during ProduceMana "
      //          "step!\n";
      // std::exit(1);
    } else if (lands[i].type == LandType::shore) {
      ++shores;
    } else {
      TapLand(lands[i], *mana_pool);
    }
  }
  TapManaCreatures(battlefield, mana_pool);

  for (int i = 0; i < shores; ++i) {
    if (IsColorStarved(lib, *mana_pool)) {
      // Either 1. Add colorless mana, OR
      ++(*mana_pool)[Color::Colorless];
      ++(*mana_pool)[Color::Total];
    } else {
      // 2. Add one of each color, but do not increment total mana.
      AddUniversalColor(mana_pool);
    }
  }
}

void ProduceMana(const Library &lib, Player *player, TurnState *state) {
  return ProduceMana(lib, player->battlefield, &state->mana_pool);
}

// Idea for color optimization: accumulate grey mana debt! Must be paid before
// end of turn.
bool IsAffordable(const ManaCost &spell_cost, const ManaCost &mana_pool) {
  // Loop checks for both Colors, as well as Total mana cost.
  for (const auto &pair : spell_cost) {
    Color color = pair.first;
    int cost_amount = pair.second;
    if (FindWithDefault(mana_pool, color, 0) < cost_amount) {
      return false;
    }
  }
  return true;
}

void PayCost(const ManaCost &spell_cost, ManaCost *mana_pool) {
  for (const auto &pair : spell_cost) {
    Color color = pair.first;
    int cost_amount = pair.second;
    int &pool_amount = (*mana_pool)[color];
    pool_amount -= cost_amount;

    if (pool_amount < 0) {
      ERROR << "Negative pool amount!\n";
    }
  }
}

double PointsFromSpell(const Spell &spell) {
  return TotalCost(spell.cost) + spell.point_bonus;
}

// Returns number of points from playing this spell.
double PlaySpell(int i, Player *player, TurnState *state) {
  PayCost(player->hand.spells[i].cost, &state->mana_pool);
  const Spell *spell = MoveSpell(i, player->hand, player->battlefield);
  if (spell != nullptr) {
    INFO << "Played " << *spell << "\n";
    DrawN(player, DrawFromPlayedSpell(*spell, *player));
    return PointsFromSpell(*spell);
  }
  ERROR << "Attempted to play a spell that doesn't exist!\n";
  return 0;
}

// Returns index to spell in hand of best spell to play.
int FindBestSpell(const Player &player, const TurnState &state) {
  const std::vector<Spell> &spells = player.hand.spells;

  int best_affordable_spell = -1;
  int best_affordable_priority = -1;
  double highest_points = 0;

  for (int i = 0; i < spells.size(); ++i) {
    if (!IsAffordable(spells[i].cost, state.mana_pool)) {
      continue;
    }
    if (spells[i].priority == 0 && player.battlefield.spells.empty()) {
      // Cannot play secondary spells if there are no creatures!
      continue;
    }
    if (spells[i].priority < best_affordable_priority) {
      continue;
    }
    const double spell_points = PointsFromSpell(spells[i]);
    if (spell_points > highest_points) {
      best_affordable_spell = i;
      highest_points = spell_points;
      best_affordable_priority = spells[i].priority;
    }
  }
  return best_affordable_spell;
}

double PlaySpells(Player *player, TurnState *state) {
  double points = 0;
  while (true) {
    const int spell_i = FindBestSpell(*player, *state);
    if (spell_i < 0) {
      break;
    } else {
      points += PlaySpell(spell_i, player, state);
    }
  }
  return points;
}

const Spell *FindBestAbility(const Player &player, const TurnState &state) {
  double highest_affordable_cost = 0;
  const Spell *best_ability = nullptr;
  for (const Spell &perm : player.battlefield.spells) {
    if (!perm.ability.has_value()) {
      continue;
    }
    if (!IsAffordable(*perm.ability, state.mana_pool)) {
      continue;
    }
    if (int ability_cost = TotalCost(*perm.ability);
        ability_cost > highest_affordable_cost) {
      highest_affordable_cost = ability_cost;
      best_ability = &perm;
    }
  }
  return best_ability;
}

Spell *FindBestOnetimeAbility(Player &player, const TurnState &state) {
  double highest_affordable_cost = 0;
  Spell *best_ability = nullptr;
  for (Spell &perm : player.battlefield.spells) {
    if (!perm.onetime_ability.has_value()) {
      continue;
    }
    if (!IsAffordable(*perm.onetime_ability, state.mana_pool)) {
      continue;
    }
    if (int ability_cost = TotalCost(*perm.onetime_ability);
        ability_cost > highest_affordable_cost) {
      highest_affordable_cost = ability_cost;
      best_ability = &perm;
    }
  }
  return best_ability;
}

// Plays onetime abilities first, and then mana sink abilities.
double PlayAbilities(Player *player, TurnState *state) {
  double points = 0;
  bool found_something = true;
  while (found_something) {
    found_something = false;
    if (Spell *spell = FindBestOnetimeAbility(*player, *state);
        spell != nullptr) {
      found_something = true;

      PayCost(*spell->onetime_ability, &state->mana_pool);
      // Can only use it once, so need to reset it to nullopt!
      spell->onetime_ability = std::nullopt;
      points += TotalCost(*spell->onetime_ability) / 2.0;
    } else if (const Spell *spell = FindBestAbility(*player, *state);
               spell != nullptr) {
      found_something = true;
      PayCost(*spell->ability, &state->mana_pool);
      points += TotalCost(*spell->ability) / 3.0;
    }
  }
  return points;
}

// Accumulates how much mana is needed for all spells in the hand.
void AggregateCosts(const Player &player, ManaCost *aggregate) {
  for (const Spell &spell : player.hand.spells) {
    (*aggregate) += spell.cost;
  }
  for (const Spell &spell : player.battlefield.spells) {
    if (spell.ability.has_value()) {
      (*aggregate) += *spell.ability;
    }
    if (spell.onetime_ability.has_value()) {
      (*aggregate) += *spell.onetime_ability;
    }
  }
}

std::vector<std::pair<float, Color>> SortNeeds(const ManaCost &agg_spell_cost,
                                               const ManaCost &mana_pool) {
  std::vector<std::pair<float, Color>> scores;
  std::vector<Color> covered;
  for (const auto &pair : agg_spell_cost) {
    Color color = pair.first;
    float demand = pair.second;
    covered.push_back(color);
    int supply = FindWithDefault(mana_pool, color, 0);
    float score = demand / (supply + 1);
    scores.emplace_back(score, color);
  }
  for (const auto &pair : mana_pool) {
    Color color = pair.first;
    if (color == Color::Total) {
      continue;
    }
    if (!Contains<Color>(covered, IsElement(color))) {
      scores.emplace_back(0.0f, color);
    }
  }
  // Sort on highest score first.
  std::sort(scores.begin(), scores.end(),
            std::greater<std::pair<float, Color>>());
  return scores;
}

// Returns which colors are missing for spells in the hand, and by how much.
// Negative values means the color is already supplied.
ManaCost FindMissingColors(const Player &player, const ManaCost &mana_pool) {
  ManaCost missing_colors;
  const int max_mana = 1 + FindWithDefault(mana_pool, Color::Total, 0);
  for (const Spell &spell : player.hand.spells) {
    if (FindWithDefault(spell.cost, Color::Total, 0) <= max_mana) {
      UpdateMaxColors(missing_colors, spell.cost);
    }
  }
  for (const Spell &spell : player.battlefield.spells) {
    if (spell.ability.has_value() &&
        FindWithDefault(*spell.ability, Color::Total, 0) <= max_mana) {
      UpdateMaxColors(missing_colors, *spell.ability);
    }
    if (spell.onetime_ability.has_value() &&
        FindWithDefault(*spell.onetime_ability, Color::Total, 0) <= max_mana) {
      UpdateMaxColors(missing_colors, *spell.onetime_ability);
    }
  }
  for (const auto [color, amount] : mana_pool) {
    missing_colors[color] -= amount;
  }
  missing_colors[Color::Total] = 0;
  return missing_colors;
}

// First color is most important to add.
std::vector<Color> ManaNeeds(const Player &player,
                             const ManaCost &agg_spell_cost,
                             const ManaCost &mana_pool) {
  std::vector<Color> priorities;
  for (const auto [color, amount] : FindMissingColors(player, mana_pool)) {
    if (amount > 0) {
      priorities.push_back(color);
    }
  }
  for (const auto [priority, color] : SortNeeds(agg_spell_cost, mana_pool)) {
    priorities.push_back(color);
  }
  return priorities;
}

// First color is most important to add.
std::vector<Color> ManaNeeds(const Player &player, const TurnState &state) {
  return ManaNeeds(player, state.agg_spell_cost, state.mana_pool);
}

int MaxPointsLand(const Player &player) {
  int max_land = -1;
  double max_points = 0;
  int iter = 0;
  for (const Land &land : player.hand.lands) {
    if (double points = PointsFromPlayedLand(land, player);
        points > max_points) {
      max_land = iter;
    }
    ++iter;
  }
  return max_land;
}

// Chooses which land to play. If plays fetch land, choose the color needed.
int ChooseLand(const std::vector<Color> &needs, const Player &player,
               const Deck &hand, bool basic_only, TurnState *state) {
  if (const int max_land = MaxPointsLand(player); max_land >= 0) {
    return max_land;
  }

  const auto &lands = hand.lands;
  int non_basic_land = -1;
  int wanted_double_land = -1;
  for (Color color : needs) {
    for (int i = 0; i < lands.size(); ++i) {
      if (lands[i].type == LandType::dual &&
          (lands[i].color == color || *lands[i].secondary == color)) {
        wanted_double_land = i;
      } else if (lands[i].color == color) {
        // Found a wanted color of basic land, play that land!
        return i;
      } else if (lands[i].type != LandType::basic) {
        non_basic_land = i;
      }
    }
    // Found wanted double land, return that.
    if (wanted_double_land >= 0) {
      return wanted_double_land;
    }
    // Didn't find the wanted color, if has fetch land, play that instead.
    if (non_basic_land >= 0 && !basic_only) {
      return non_basic_land;
    }
  }
  // Play any land if possible...
  return 0;
}

// Returns points from played lands.
double PlayLand(Player *player, TurnState *state) {
  const auto &lands = player->hand.lands;
  if (lands.empty()) {
    INFO << "No lands in hand.\n";
    return 0;
  }

  const std::vector<Color> needs = ManaNeeds(*player, *state);
  const int i = ChooseLand(needs, *player, player->hand, false, state);
  const Land *played = nullptr;

  if (lands[i].type == LandType::fetch) {
    // Sacrifice the land, and search for another land instead.
    // The searched land cannot be tapped this turn.
    MoveLand(i, player->hand, player->graveyard);
    const int search = ChooseLand(needs, *player, player->library, true, state);
    played = MoveLand(search, player->library, player->battlefield);
    if (played) {
      INFO << "Fetched and played " << *played << "\n";
    } else {
      INFO << "Attempted fetch but could not play any land.\n";
    }
  } else if (lands[i].type == LandType::dual) {
    played = MoveLand(i, player->hand, player->battlefield);
    if (played) {
      INFO << "Played double land " << *played << "\n";
    } else {
      INFO << "Could not play any land.\n";
    }
  } else { // Not a fetch land.
    played = MoveLand(i, player->hand, player->battlefield);
    if (played) {
      TapLand(*played, state->mana_pool);
      INFO << "Played and tapped " << *played << "\n";
    } else {
      INFO << "Could not play any land.\n";
    }
  }

  if (played != nullptr) {
    return PointsFromPlayedLand(*played, *player);
  }

  return 0;
}

double PointsFromBattlefield(const Player &player) {
  double points = 0;
  for (const Spell &spell : player.battlefield.spells) {
    points += 0.5 * PointsFromSpell(spell);
  }
  return points;
}

// Returns #points.
double PlayTurn(const Library &lib, Player *player) {
  double points = 0;
  TurnState state;

  // Get some points for previously played creatures. Needs to be calculated
  // before playing new spells.
  const double battlefield_advantage = PointsFromBattlefield(*player);

  // Upkeep
  DrawOne(player);
  INFO << "Hand " << player->hand << "\n";
  AggregateCosts(*player, &state.agg_spell_cost);
  ProduceMana(lib, player, &state);

  // Main phase
  points += PlayLand(player, &state);
  INFO << "Mana " << state.mana_pool << "\n";
  points += PlaySpells(player, &state);
  points += PlayAbilities(player, &state);
  points += battlefield_advantage;
  if (points <= 0) {
    // If could not do anything useful, not even attacking, then minus one
    // point.
    points -= 1;
  }
  return points;
}

// Returns true or false, depending on hand, and number of mulligans in the
// past.
using MulliganStrategy = std::function<bool(const Deck &, int)>;

bool NoStrategy(const Deck &hand, int n) { return false; }

bool SimpleStrategy(const Deck &hand, int n) {
  int num_lands = hand.lands.size();
  // Observation: should play if has between 2 - 5 lands in initial hand!
  if (n == 1 && (num_lands <= 1 || num_lands >= 6)) {
    return true;
  }
  if (n == 2 && (num_lands <= 1 || num_lands >= 5)) {
    return true;
  }
  return false;
}

void BottomOne(const Library &lib, Player *player) {
  ManaCost hand_pool;
  ProduceMana(lib, player->hand, &hand_pool);
  ManaCost hand_cost;
  AggregateCosts(*player, &hand_cost);

  auto needs = SortNeeds(hand_cost, hand_pool);

  if (player->hand.lands.size() > player->hand.spells.size()) {
    // Bottom a land.
    // NOTE: doesn't have logic for fetch lands... or other lands...
    Color least_wanted = needs.back().second;
    int worst_land =
        Find<Land>(player->hand.lands, [least_wanted](const Land &land) {
          return land.color == least_wanted;
        });
    if (worst_land < 0) {
      INFO << "The least_wanted color " << least_wanted
           << " is not present in the ManaPool!\n";
      INFO << hand_cost << "\n";
      INFO << hand_pool << "\n";
      // Can happen if Hand is : WBBBBBB
      // And lands are : BBB
      worst_land = 0;
    }
    MoveLand(worst_land, player->hand, player->library);
  } else {
    const auto &spells = player->hand.spells;
    int worst_spell = 0;
    int least_priority = 100;
    for (int i = 0; i < spells.size(); ++i) {
      if (!IsAffordable(spells[i].cost, hand_pool) &&
          spells[i].priority <= least_priority) {
        worst_spell = i;
        least_priority = spells[i].priority;
      }
    }
    MoveSpell(worst_spell, player->hand, player->library);
  }
}

// First Mulligan, n==1. Second mulligan, n==2.
void DrawMulligan(const Library &lib, Player *player, const int n) {
  // DrawN(player, 7 - n);
  // TODO: actually draw 7 and return 1 spell of choice...
  DrawN(player, 7);
  for (int i = 0; i < n; ++i) {
    BottomOne(lib, player);
    if (player->hand.Size() + i + 1 != 7) {
      ERROR << "After mulligan " << n << ", incorrect hand size "
            << player->hand.Size() << " !\n";
    }
  }
}

Player StartingHand(const Library &lib, const Deck &deck,
                    const MulliganStrategy &strategy) {
  Player player;
  player.library = deck;
  DrawN(&player, 7);

  for (int i = 1; i < 7 && strategy(player.hand, i); ++i) {
    INFO << "Mulligan!\n";
    player = Player();
    player.library = deck;
    DrawMulligan(lib, &player, i);
  }

  return player;
}

int BoardPoints(const Player &player) {
  int sum = 0;
  for (const Spell &spell : player.battlefield.spells) {
    sum += TotalCost(spell.cost);
  }
  return sum;
}

double PlayGame(const Library &lib, const Deck &deck,
                const MulliganStrategy &strategy, int turns) {
  INFO << "-- Game start ------------- \n";
  float score = 0.0f;

  Player player = StartingHand(lib, deck, strategy);

  for (int turn = 0; turn < turns; ++turn) {
    INFO << "-- Begin turn " << (turn + 1) << " ------------- \n";
    score += PlayTurn(lib, &player);
    // std::cout << "Score at turn " << (turn + 1) << ": " << score << "\n";
  }
  return score;
}

// -----------------------------------------------------------------------------

TEST(ProduceManaBasicLands) {
  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::White));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Red));

  Library lib = Library::Builder()
                    .AddSpell(MakeSpell("BU"))
                    .AddSpell(MakeSpell("R"))
                    .Build();
  TurnState state;
  ProduceMana(lib, &player, &state);

  if (std::string mana = ToString(state.mana_pool); mana != "WBBR") {
    Fail("Expected WBBR but found " + mana);
  }
}

TEST(ChoseLandSimpleNeed) {
  Player player;
  player.hand.lands.push_back(BasicLand(Color::White));
  player.hand.lands.push_back(BasicLand(Color::Black));
  player.hand.spells.push_back(MakeSpell("BB"));
  player.hand.spells.push_back(MakeSpell("B4"));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  Library lib = Library::Builder().AddSpell(MakeSpell("BB")).Build();
  TurnState state;
  AggregateCosts(player, &state.agg_spell_cost);
  ProduceMana(lib, &player, &state);

  if (std::string mana = ToString(state.agg_spell_cost); mana != "BBB4") {
    Fail("Expected BBB4 but found " + mana);
  }
  if (std::string mana = ToString(state.mana_pool); mana != "B") {
    Fail("Expected B but found " + mana);
  }

  std::vector<Color> needs = ManaNeeds(player, state);

  int i = ChooseLand(needs, player, player.hand, false, &state);
  if (i != 1) {
    Fail("Expected to pick B, instead picked land " + std::to_string(i));
  }
}

TEST(PrioritizeColorThatEnablesSpell) {
  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::White));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  player.hand.lands.push_back(BasicLand(Color::White));
  player.hand.lands.push_back(BasicLand(Color::Red));

  player.hand.spells.push_back(MakeSpell("W2"));
  player.hand.spells.push_back(MakeSpell("BR1"));
  player.hand.spells.push_back(MakeSpell("WW2"));
  player.hand.spells.push_back(MakeSpell("WW3"));
  // Has many more white spells, but should prioritize enabling BR1 before
  // enabling WW2 because is playable same turn.

  Library lib = Library::Builder().AddSpell(MakeSpell("BB")).Build();
  TurnState state;
  AggregateCosts(player, &state.agg_spell_cost);
  ProduceMana(lib, &player, &state);

  std::vector<Color> needs = ManaNeeds(player, state);
  int i = ChooseLand(needs, player, player.hand, false, &state);
  if (i != 1) {
    Fail("Expected to pick R, instead picked land " + std::to_string(i));
  }
}

TEST(PlayTurnSimple) {
  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  // Has one spell in library. Will draw one. Then must play that one.
  player.library.spells.push_back(MakeSpell("BB", 1, "Foo"));

  Library lib = Library::Builder().AddSpell(MakeSpell("BB")).Build();

  double points = PlayTurn(lib, &player);
  if (player.battlefield.spells.empty() ||
      player.battlefield.spells.front().name != "Foo") {
    Fail("Expected Spell to be played");
  }
  if (static_cast<int>(points) != 2) {
    Fail("Expected 2 points, but found " + std::to_string(points));
  }
}

TEST(PlayTurnExistingCreature) {
  Player player;
  player.battlefield.spells.push_back(MakeSpell("B3", 1, "Foo"));
  player.library.lands.push_back(BasicLand(Color::White));

  Library lib = Library::Builder().AddSpell(MakeSpell("B3")).Build();

  double points = PlayTurn(lib, &player);
  if (static_cast<int>(points) != 2) {
    Fail("Expected 2 points, but found " + std::to_string(points));
  }
}

TEST(PlayTurnNotEnoughMana) {
  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::White));

  // Has one spell in library. Will draw one. Not enough mana to play it.
  player.library.spells.push_back(MakeSpell("BB", 1, "Foo"));

  Library lib = Library::Builder().AddSpell(MakeSpell("BB")).Build();

  double points = PlayTurn(lib, &player);
  if (!player.battlefield.spells.empty()) {
    Fail("Expected no spells to be played but found " +
         player.battlefield.spells.front().name);
  }
  // Gets minus one point if cannot play a spell.
  if (static_cast<int>(points) != -1) {
    Fail("Expected -1 points, but found " + std::to_string(points));
  }
}

TEST(PlayBestSpell) {
  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  player.hand.spells.push_back(MakeSpell("BB", 1, "Small"));
  player.hand.spells.push_back(MakeSpell("B3", 1, "Big"));

  // Will draw one.
  player.library.lands.push_back(BasicLand(Color::Black));

  Library lib = Library::Builder().AddSpell(MakeSpell("BB")).Build();

  double points = PlayTurn(lib, &player);
  if (player.battlefield.spells.empty() ||
      player.battlefield.spells.front().name != "Big") {
    Fail("Expected Big Spell to be played");
  }
  if (static_cast<int>(points) != 4) {
    Fail("Expected 4 points, but found " + std::to_string(points));
  }
}

TEST(PlayBestSpellRespectPriority) {
  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  player.hand.spells.push_back(MakeSpell("BB", 5, "Important"));
  player.hand.spells.push_back(MakeSpell("B3", 1, "Big"));

  // Will draw one.
  player.library.lands.push_back(BasicLand(Color::Black));

  Library lib = Library::Builder().AddSpell(MakeSpell("BB")).Build();

  double points = PlayTurn(lib, &player);
  if (player.battlefield.spells.empty() ||
      player.battlefield.spells.front().name != "Important") {
    Fail("Expected Big Spell to be played");
  }
  if (static_cast<int>(points) != 2) {
    Fail("Expected 2 points, but found " + std::to_string(points));
  }
}

TEST(PlaySeveralSpells) {
  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  player.hand.spells.push_back(MakeSpell("BB", 1, "Small"));
  player.hand.spells.push_back(MakeSpell("BB", 1, "Small"));
  player.hand.spells.push_back(MakeSpell("B", 1, "Tiny"));

  // Will draw one land.
  player.library.lands.push_back(BasicLand(Color::Black));

  Library lib = Library::Builder().AddSpell(MakeSpell("BB")).Build();

  // Can play two Small spells, but not Tiny.
  double points = PlayTurn(lib, &player);
  if (player.battlefield.spells.empty() ||
      player.battlefield.spells.front().name != "Small") {
    Fail("Expected Small Spell to be played first");
  }
  if (player.battlefield.spells.size() < 2 ||
      player.battlefield.spells[1].name != "Small") {
    Fail("Expected Small Spell to be played second");
  }
  if (player.hand.spells.empty() || player.hand.spells.front().name != "Tiny") {
    Fail("Expected Tiny Spell to not be played");
  }
  if (static_cast<int>(points) != 4) {
    Fail("Expected 4 points, but found " + std::to_string(points));
  }
}

TEST(PlayAbilities) {
  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  // Has one ability in battlefield.
  player.battlefield.spells.push_back(
      MakeSpell("B", 1, "Foo").AddAbility("B2"));

  // Will draw a land. Will have 6 mana afterwards.
  player.library.lands.push_back(BasicLand(Color::Black));

  Library lib = Library::Builder().AddSpell(MakeSpell("B")).Build();

  double points = PlayTurn(lib, &player);
  // Gets 6/3 = 2 points for playing the same ability twice.
  if (static_cast<int>(points) != 2) {
    Fail("Expected 2 points, but found " + std::to_string(points));
  }
}

TEST(PlayOnetimeAbilities) {
  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  // Has one ability in battlefield.
  player.battlefield.spells.push_back(
      MakeSpell("B", 1, "Foo").AddAbility("B3").AddOnetimeAbility("BB"));

  // Will draw a land. Will have 5 mana afterwards.
  player.library.lands.push_back(BasicLand(Color::Black));

  Library lib = Library::Builder().AddSpell(MakeSpell("B")).Build();

  double points = PlayTurn(lib, &player);
  // Gets 2/2 points for playing the onetime once.
  if (static_cast<int>(points) != 1) {
    Fail("Expected 1 points, but found " + std::to_string(points));
  }
}
