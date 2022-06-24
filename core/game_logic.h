#pragma once

#include "../common/container.h"
#include "../common/random.h"
#include "../common/test.h"
#include "card_logic.h"
#include "contribution.h"
#include "library.h"

struct TurnState {
  ManaCost mana_pool;
  ManaCost agg_spell_cost;
};

void DrawOne(ThreadsafeRandom &rand, Player *player) {
  auto &lib = player->library;
  int total_cards = lib.spells.size() + lib.lands.size();
  if (total_cards <= 0) {
    ERROR << "Cannot draw card because the library is empty!\n";
    return;
  }
  int picked = rand.Rand() % total_cards;
  // INFO << "Rand pick " << picked << "\n";
  if (picked >= lib.spells.size()) {
    // Picked a land
    picked -= lib.spells.size();
    Land *land = MoveLand(picked, player->library, player->hand);
    INFO << "Drew " << *land << "\n";
  } else {
    // Picked a non-land
    SpellView *spell = MoveSpell(picked, player->library, player->hand);
    INFO << "Drew " << *spell << "\n";
  }
}

void DrawN(ThreadsafeRandom &rand, Player *player, int n) {
  for (int i = 0; i < n; ++i) {
    DrawOne(rand, player);
  }
}

void TapLand(const Land &land, ManaCost &mana_pool) {
  if (land.type == LandType::fetch) {
    FATAL << "Attempted to tap a fetch land for mana!\n";
    return;
  }
  mana_pool += land.colors;
}

bool IsColorStarved(const Library &lib, const ManaCost &mana_pool) {
  if (mana_pool.FindValue(lib.PrimaryColor()) < 1) {
    return true;
  }
  if (mana_pool.FindValue(lib.SecondaryColor()) < 1) {
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
      // FATAL << "Attempted to tap a fetch land for mana during ProduceMana "
      //          "step!\n";
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
    if (mana_pool.FindValue(color) < cost_amount) {
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

    CHECK(pool_amount >= 0) << "Negative pool amount!\n";
  }
}

double PointsFromSpell(const SpellView spell) {
  return TotalCost(spell->cost) + spell->point_bonus;
}

// Returns number of points from playing this spell.
double PlaySpell(int i, Player *player, TurnState *state,
                 ThreadsafeRandom &rand, CardContributions *contributions) {
  PayCost(player->hand.spells[i]->cost, &state->mana_pool);
  const SpellView *spell = MoveSpell(i, player->hand, player->battlefield);
  if (spell != nullptr) {
    INFO << "Played " << *spell << "\n";
    DrawN(rand, player, DrawFromPlayedSpell(*spell, *player));
    double delta = PointsFromSpell(*spell);
    AddDelta(delta, spell->name(), contributions);
    return delta;
  }
  ERROR << "Attempted to play a spell that doesn't exist!\n";
  return 0;
}

// Returns index to spell in hand of best spell to play.
int FindBestSpell(const Player &player, const TurnState &state) {
  const std::vector<SpellView> &spells = player.hand.spells;

  int best_affordable_spell = -1;
  int best_affordable_priority = -1;
  double highest_points = 0;

  for (int i = 0; i < spells.size(); ++i) {
    if (!IsAffordable(spells[i].cost(), state.mana_pool)) {
      continue;
    }
    if (spells[i]->priority == 0 && player.battlefield.spells.empty()) {
      // Cannot play secondary spells if there are no creatures!
      continue;
    }
    if (spells[i]->priority < best_affordable_priority) {
      continue;
    }
    const double spell_points = PointsFromSpell(spells[i]);
    if (spell_points > highest_points) {
      best_affordable_spell = i;
      highest_points = spell_points;
      best_affordable_priority = spells[i]->priority;
    }
  }
  return best_affordable_spell;
}

double PlaySpells(Player *player, TurnState *state, ThreadsafeRandom &rand,
                  CardContributions *contributions) {
  double points = 0;
  while (true) {
    const int spell_i = FindBestSpell(*player, *state);
    if (spell_i < 0) {
      break;
    } else {
      points += PlaySpell(spell_i, player, state, rand, contributions);
    }
  }
  return points;
}

const SpellView *FindBestAbility(const Player &player, const TurnState &state) {
  double highest_affordable_cost = 0;
  const SpellView *best_ability = nullptr;
  for (const SpellView &perm : player.battlefield.spells) {
    if (!perm->ability.has_value()) {
      continue;
    }
    if (!IsAffordable(*perm->ability, state.mana_pool)) {
      continue;
    }
    if (int ability_cost = TotalCost(*perm->ability);
        ability_cost > highest_affordable_cost) {
      highest_affordable_cost = ability_cost;
      best_ability = &perm;
    }
  }
  return best_ability;
}

SpellView *FindBestOnetimeAbility(Player &player, const TurnState &state) {
  double highest_affordable_cost = 0;
  SpellView *best_ability = nullptr;
  for (SpellView &perm : player.battlefield.spells) {
    const ManaCost *onetime = perm.onetime_ability();
    if (onetime == nullptr) {
      continue;
    }
    if (!IsAffordable(*onetime, state.mana_pool)) {
      continue;
    }
    if (int ability_cost = TotalCost(*onetime);
        ability_cost > highest_affordable_cost) {
      highest_affordable_cost = ability_cost;
      best_ability = &perm;
    }
  }
  return best_ability;
}

// Plays onetime abilities first, and then mana sink abilities.
double PlayAbilities(Player *player, TurnState *state,
                     CardContributions *contributions) {
  double points = 0;
  bool found_something = true;
  while (found_something) {
    found_something = false;

    if (SpellView *spell = FindBestOnetimeAbility(*player, *state);
        spell != nullptr) {
      found_something = true;

      const ManaCost *onetime = spell->onetime_ability();
      PayCost(*onetime, &state->mana_pool);
      double delta = TotalCost(*onetime) / 2.0;
      points += delta;
      // Can only use it once, so need to reset it to nullopt!
      spell->use_onetime_ability();
      AddDelta(delta, spell->name(), contributions);
    } else if (const SpellView *spell = FindBestAbility(*player, *state);
               spell != nullptr) {
      found_something = true;
      PayCost(*spell->ability(), &state->mana_pool);
      double delta = TotalCost(*spell->ability()) / 3.0;
      points += delta;
      AddDelta(delta, spell->name(), contributions);
    }
  }
  return points;
}

// Accumulates how much mana is needed for all spells in the hand.
void AggregateCosts(const Player &player, ManaCost *aggregate) {
  for (const SpellView spell : player.hand.spells) {
    (*aggregate) += spell.cost();
  }
  for (const SpellView spell : player.battlefield.spells) {
    if (spell->ability.has_value()) {
      (*aggregate) += *spell->ability;
    }
    if (spell.onetime_ability() != nullptr) {
      (*aggregate) += *spell.onetime_ability();
    }
  }
}

// Returns greatest need first.
std::vector<std::pair<float, Color>> SortNeeds(const ManaCost &agg_spell_cost,
                                               const ManaCost &mana_pool) {
  std::vector<std::pair<float, Color>> scores;
  std::vector<Color> covered;
  for (const auto &pair : agg_spell_cost) {
    Color color = pair.first;
    float demand = pair.second;
    covered.push_back(color);
    int supply = mana_pool.FindValue(color);
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
  const int max_mana = 1 + mana_pool.FindValue(Color::Total);
  for (const SpellView spell : player.hand.spells) {
    if (spell->cost.FindValue(Color::Total) <= max_mana) {
      UpdateMaxColors(missing_colors, spell->cost);
    }
  }
  for (const SpellView spell : player.battlefield.spells) {
    if (spell.ability().has_value() &&
        spell.ability()->FindValue(Color::Total) <= max_mana) {
      UpdateMaxColors(missing_colors, *spell.ability());
    }
    if (spell.onetime_ability() != nullptr &&
        spell.onetime_ability()->FindValue(Color::Total) <= max_mana) {
      UpdateMaxColors(missing_colors, *spell.onetime_ability());
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
    if (double points = PointsFromPlayedLand(land, player, nullptr);
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
  if (hand.lands.empty()) {
    return -1;
  }
  if (const int max_land = MaxPointsLand(player); max_land >= 0) {
    return max_land;
  }

  const auto &lands = hand.lands;
  int non_basic_land = -1;
  int wanted_double_land = -1;
  for (Color color : needs) {
    for (int i = 0; i < lands.size(); ++i) {
      if (lands[i].type == LandType::dual && lands[i].colors.contains(color)) {
        wanted_double_land = i;
      } else if (lands[i].type == LandType::basic &&
                 lands[i].colors.contains(color)) {
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

const Land *PlayLand(Player *player, TurnState *state) {
  const std::vector<Color> needs = ManaNeeds(*player, *state);
  const int i = ChooseLand(needs, *player, player->hand, false, state);
  if (i < 0) {
    return nullptr;
  }

  const auto &lands = player->hand.lands;
  switch (lands[i].type) {
  case LandType::basic:
  case LandType::shore: {
    const Land *played = MoveLand(i, player->hand, player->battlefield);
    if (played) {
      TapLand(*played, state->mana_pool);
    }
    return played;
  }
  case LandType::dual: {
    return MoveLand(i, player->hand, player->battlefield);
  }
  case LandType::fetch: {
    // Sacrifice the land, and search for another land instead.
    // The searched land cannot be tapped this turn.
    MoveLand(i, player->hand, player->graveyard);
    const int search = ChooseLand(needs, *player, player->library, true, state);
    return MoveLand(search, player->library, player->battlefield);
  }
  }
  return nullptr;
}

// Returns points from played lands.
double PlayLand(Player *player, TurnState *state,
                CardContributions *contributions) {
  if (const Land *played = PlayLand(player, state); played != nullptr) {
    INFO << "Played Land " << *played << "\n";
    return PointsFromPlayedLand(*played, *player, contributions);
  } else {
    INFO << "Could not play any land.\n";
  }
  return 0;
}

double PointsFromBattlefield(const Player &player,
                             CardContributions *contributions) {
  constexpr double kLastingContributionRatio = 0.5;
  double points = 0;
  for (const SpellView spell : player.battlefield.spells) {
    double delta = kLastingContributionRatio * PointsFromSpell(spell);
    points += delta;
    AddDelta(delta, spell->name, contributions);
  }
  return points;
}

// Penalize leftover mana to avoid suggesting decks with mana flooding.
double PenaltyFromLeftoverMana(const Player &player, const TurnState &state,
                               CardContributions *contributions) {
  constexpr double kPenaltyRatio = 0.5;
  double penalty = -kPenaltyRatio * state.mana_pool.FindValue(Color::Total);
  CHECK(penalty <= 0) << "Cannot have negative mana but total mana left is "
                      << state.mana_pool.FindValue(Color::Total);

  // Attribute penalty to spells in the hand, since if has significant leftover
  // mana and cannot play spell, then the spell may be too expensive or has too
  // difficult mana requirements.
  for (const SpellView spell : player.hand.spells) {
    // Cannot divide by zero since must be >1 if entered the loop.
    double delta = penalty / player.hand.spells.size();
    AddDelta(delta, spell.name(), contributions);
  }
  return penalty;
}

// Returns #points.
double PlayTurn(const Library &lib, Player *player, ThreadsafeRandom &rand,
                CardContributions *contributions) {
  double points = 0;
  TurnState state;

  // Get some points for previously played creatures. Needs to be calculated
  // before playing new spells.
  const double battlefield_advantage =
      PointsFromBattlefield(*player, contributions);

  // Upkeep
  DrawOne(rand, player);
  INFO << "Hand " << player->hand << "\n";
  AggregateCosts(*player, &state.agg_spell_cost);
  ProduceMana(lib, player, &state);

  // Main phase
  points += PlayLand(player, &state, contributions);
  INFO << "Mana " << state.mana_pool << "\n";
  points += PlaySpells(player, &state, rand, contributions);
  points += PlayAbilities(player, &state, contributions);
  points += battlefield_advantage;
  points += PenaltyFromLeftoverMana(*player, state, contributions);
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
          return land.colors.contains(least_wanted);
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
      if (!IsAffordable(spells[i]->cost, hand_pool) &&
          spells[i]->priority <= least_priority) {
        worst_spell = i;
        least_priority = spells[i]->priority;
      }
    }
    MoveSpell(worst_spell, player->hand, player->library);
  }
}

// First Mulligan, n==1. Second mulligan, n==2.
void DrawMulligan(const Library &lib, Player *player, ThreadsafeRandom &rand,
                  const int n) {
  // DrawN(player, 7 - n);
  // TODO: actually draw 7 and return 1 spell of choice...
  DrawN(rand, player, 7);
  for (int i = 0; i < n; ++i) {
    BottomOne(lib, player);
    if (player->hand.Size() + i + 1 != 7) {
      ERROR << "After mulligan " << n << ", incorrect hand size "
            << player->hand.Size() << " !\n";
    }
  }
}

Player StartingHand(const Library &lib, const Deck &deck,
                    ThreadsafeRandom &rand, const MulliganStrategy &strategy) {
  // Note: No need to Shuffle, since draws randomly rather than from top inside
  // DrawOne().
  Player player;
  player.library = deck;
  DrawN(rand, &player, 7);

  for (int i = 1; i < 7 && strategy(player.hand, i); ++i) {
    INFO << "Mulligan!\n";
    player = Player();
    player.library = deck;
    DrawMulligan(lib, &player, rand, i);
  }

  return player;
}

int BoardPoints(const Player &player) {
  int sum = 0;
  for (const SpellView spell : player.battlefield.spells) {
    sum += TotalCost(spell->cost);
  }
  return sum;
}

double PlayGame(const Library &lib, const Deck &deck,
                const MulliganStrategy &strategy, int turns,
                ThreadsafeRandom &rand,
                CardContributions *contributions = nullptr) {
  INFO << "-- Game start ------------- \n";
  float score = 0.0f;
  Player player = StartingHand(lib, deck, rand, strategy);

  for (int turn = 0; turn < turns; ++turn) {
    INFO << "-- Begin turn " << (turn + 1) << " ------------- \n";
    score += PlayTurn(lib, &player, rand, contributions);
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
  EXPECT_EQ(ToString(state.mana_pool), "WBBR");
}

TEST(ChoseLandSimpleNeed) {
  Spell bb = MakeSpell("BB");
  Spell b4 = MakeSpell("B4");

  Player player;
  player.hand.lands.push_back(BasicLand(Color::White));
  player.hand.lands.push_back(BasicLand(Color::Black));
  player.hand.spells.push_back(bb);
  player.hand.spells.push_back(b4);
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  Library lib = Library::Builder().AddSpell(bb).Build();
  TurnState state;
  AggregateCosts(player, &state.agg_spell_cost);
  ProduceMana(lib, &player, &state);

  EXPECT_EQ(ToString(state.agg_spell_cost), "BBB4");
  EXPECT_EQ(ToString(state.mana_pool), "B");

  EXPECT_TRUE(IsSwamp(*PlayLand(&player, &state)));
}

TEST(PrioritizeColorThatEnablesSpell) {
  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::White));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  player.hand.lands.push_back(BasicLand(Color::White));
  player.hand.lands.push_back(BasicLand(Color::Red));

  Spell s1 = MakeSpell("W2");
  Spell s2 = MakeSpell("BR1");
  Spell s3 = MakeSpell("WW2");
  Spell s4 = MakeSpell("WW3");

  player.hand.spells.push_back(s1);
  player.hand.spells.push_back(s2);
  player.hand.spells.push_back(s3);
  player.hand.spells.push_back(s4);
  // Has many more white spells, but should prioritize enabling BR1 before
  // enabling WW2 because is playable same turn.

  Library lib = Library::Builder().AddSpell(MakeSpell("BB")).Build();
  TurnState state;
  AggregateCosts(player, &state.agg_spell_cost);
  ProduceMana(lib, &player, &state);

  EXPECT_TRUE(IsMountain(*PlayLand(&player, &state)));
  EXPECT_EQ(ToString(state.mana_pool), "WBR");
}

TEST(PrioritizeColorThatEnablesFutureSpell) {
  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Red));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  player.hand.lands.push_back(BasicLand(Color::White));
  player.hand.lands.push_back(BasicLand(Color::Red));
  player.hand.lands.push_back(BasicLand(Color::Black));

  Spell s1 = MakeSpell("BR2");
  Spell s2 = MakeSpell("W4");
  Spell s3 = MakeSpell("R3");
  Spell s4 = MakeSpell("R4");
  Spell s5 = MakeSpell("R5");

  player.hand.spells.push_back(s1);
  player.hand.spells.push_back(s2);
  player.hand.spells.push_back(s3);
  player.hand.spells.push_back(s4);
  player.hand.spells.push_back(s5);
  // Has many more red spells, but should prioritize enabling W before
  // playing R.

  Library lib = Library::Builder().AddSpell(MakeSpell("B")).Build();
  TurnState state;
  AggregateCosts(player, &state.agg_spell_cost);
  ProduceMana(lib, &player, &state);

  EXPECT_TRUE(IsPlains(*PlayLand(&player, &state)));
  EXPECT_EQ(ToString(state.mana_pool), "WBR");
}

TEST(PlayFetchLandForLandThatEnablesFutureSpell) {
  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Red));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  player.library.lands.push_back(BasicLand(Color::White));
  player.library.lands.push_back(BasicLand(Color::Red));
  player.library.lands.push_back(BasicLand(Color::Black));
  player.hand.lands.push_back(FetchLand());

  Spell s1 = MakeSpell("BR2");
  Spell s2 = MakeSpell("W4");
  Spell s3 = MakeSpell("R3");
  Spell s4 = MakeSpell("R4");
  Spell s5 = MakeSpell("R5");

  player.hand.spells.push_back(s1);
  player.hand.spells.push_back(s2);
  player.hand.spells.push_back(s3);
  player.hand.spells.push_back(s4);
  player.hand.spells.push_back(s5);
  // Has many more red spells, but should prioritize enabling W before
  // playing R.

  Library lib = Library::Builder().AddSpell(MakeSpell("B")).Build();
  TurnState state;
  AggregateCosts(player, &state.agg_spell_cost);
  ProduceMana(lib, &player, &state);

  // Uses fetch land to play plains.
  EXPECT_TRUE(IsPlains(*PlayLand(&player, &state)));
  // Fetched land is already tapped.
  EXPECT_EQ(ToString(state.mana_pool), "BR");
}

TEST(PlayTurnSimple) {
  ThreadsafeRandom rand;
  Spell bb = MakeSpell("BB", 1, "Foo");

  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  // Has one spell in library. Will draw one. Then must play that one.
  player.library.spells.push_back(bb);
  Library lib = Library::Builder().AddSpell(bb).Build();

  CardContributions contributions = MakeContributionMaps(player.library.spells);
  double points = PlayTurn(lib, &player, rand, &contributions);
  if (player.battlefield.spells.empty() ||
      player.battlefield.spells.front().name() != "Foo") {
    Fail("Expected Spell to be played");
  }
  EXPECT_NEAR(points, 2);
  EXPECT_EQ(GetContribution("Foo", &contributions), 2);
}

TEST(PlayTurnExistingCreature) {
  ThreadsafeRandom rand;
  Spell b3 = MakeSpell("B3", 1, "Foo");

  Player player;
  player.battlefield.spells.push_back(b3);
  player.library.lands.push_back(BasicLand(Color::White));
  Library lib = Library::Builder().AddSpell(b3).Build();

  CardContributions contributions =
      MakeContributionMaps(player.battlefield.spells);
  double points = PlayTurn(lib, &player, rand, &contributions);
  EXPECT_NEAR(points, 2 - 0.5);
  EXPECT_EQ(GetContribution("Foo", &contributions), 2);
}

TEST(PlayTurnNotEnoughMana) {
  ThreadsafeRandom rand;
  Spell bb = MakeSpell("BB", 1, "Foo");
  Spell bb2 = MakeSpell("BB2", 1, "Bar");

  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::White));
  player.hand.spells.push_back(bb);
  player.hand.spells.push_back(bb2);

  // Has one land in library. Will draw one Plains.
  Library lib = Library::Builder().AddLand(BasicLand(Color::White)).Build();
  player.library.lands.push_back(BasicLand(Color::White));

  CardContributions contributions = MakeContributionMaps(player.hand.spells);
  double points = PlayTurn(lib, &player, rand, &contributions);
  EXPECT_TRUE(player.battlefield.spells.empty());

  // Gets minus 3/2 point from 3 unused mana.
  EXPECT_NEAR(points, -1.5);
  // The penalty is attributed equally to the spells in hand.
  EXPECT_NEAR(GetContribution("Foo", &contributions), -0.75);
  EXPECT_NEAR(GetContribution("Bar", &contributions), -0.75);
}

TEST(PlayBestSpell) {
  ThreadsafeRandom rand;
  Spell bb = MakeSpell("BB", 1, "Small");
  Spell b3 = MakeSpell("B3", 1, "Big");

  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  player.hand.spells.push_back(bb);
  player.hand.spells.push_back(b3);

  // Will draw one.
  player.library.lands.push_back(BasicLand(Color::Black));
  Library lib = Library::Builder().AddSpell(bb).Build();

  CardContributions contributions = MakeContributionMaps(player.hand.spells);
  double points = PlayTurn(lib, &player, rand, &contributions);

  EXPECT_EQ(player.battlefield.spells.size(), 1);
  EXPECT_EQ(player.battlefield.spells.front().name(), "Big");
  EXPECT_NEAR(points, 4);
  EXPECT_EQ(GetContribution("Big", &contributions), 4);
}

TEST(PlayBestSpellRespectPriority) {
  ThreadsafeRandom rand;
  Spell bb = MakeSpell("BB", 5, "Important");
  Spell b3 = MakeSpell("B3", 1, "Big");

  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  player.hand.spells.push_back(bb);
  player.hand.spells.push_back(b3);

  // Will draw one.
  player.library.lands.push_back(BasicLand(Color::Black));
  Library lib = Library::Builder().AddSpell(MakeSpell("BB7")).Build();

  double points = PlayTurn(lib, &player, rand, nullptr);
  EXPECT_EQ(player.battlefield.spells.size(), 1);
  EXPECT_EQ(player.battlefield.spells.front().name(), "Important");

  // 2 points for important spell, -1 point for mana not spent.
  EXPECT_NEAR(points, 2 - 1);
}

TEST(PlaySeveralSpells) {
  ThreadsafeRandom rand;
  Spell bb = MakeSpell("BB", 1, "Small");
  Spell b = MakeSpell("B", 1, "Tiny");

  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  player.hand.spells.push_back(bb);
  player.hand.spells.push_back(bb);
  player.hand.spells.push_back(b);

  // Will draw one land.
  player.library.lands.push_back(BasicLand(Color::Black));
  Library lib = Library::Builder().AddSpell(bb).Build();

  // Can play two Small spells, but not Tiny.
  double points = PlayTurn(lib, &player, rand, nullptr);

  if (player.battlefield.spells.empty() ||
      player.battlefield.spells.front().name() != "Small") {
    Fail("Expected Small Spell to be played first");
  }
  if (player.battlefield.spells.size() < 2 ||
      player.battlefield.spells[1].name() != "Small") {
    Fail("Expected Small Spell to be played second");
  }
  if (player.hand.spells.empty() ||
      player.hand.spells.front().name() != "Tiny") {
    Fail("Expected Tiny Spell to not be played");
  }
  EXPECT_NEAR(points, 4);
}

TEST(PlayAbilities) {
  ThreadsafeRandom rand;
  Spell b = MakeSpell("B", 1, "Foo").AddAbility("B2");

  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  // Has one ability in battlefield.
  player.battlefield.spells.push_back(b);

  // Will draw a land. Will have 6 mana afterwards.
  player.library.lands.push_back(BasicLand(Color::Black));
  Library lib = Library::Builder().AddSpell(b).Build();

  CardContributions contributions =
      MakeContributionMaps(player.battlefield.spells);
  double points = PlayTurn(lib, &player, rand, &contributions);
  // + 1/2 points for existing creature
  // + 6/3 = 2 points for playing the same ability twice.
  EXPECT_NEAR(points, 2.5);
  EXPECT_NEAR(GetContribution("Foo", &contributions), 2.5);
}

TEST(PlayOnetimeAbilities) {
  ThreadsafeRandom rand;
  Spell b = MakeSpell("B", 1, "Foo").AddAbility("B4").AddOnetimeAbility("B3");

  Player player;
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));
  player.battlefield.lands.push_back(BasicLand(Color::Black));

  // Has one ability in battlefield.
  player.battlefield.spells.push_back(b);

  // Will draw a land. Will have 5 mana afterwards.
  player.library.lands.push_back(BasicLand(Color::Black));
  Library lib = Library::Builder().AddSpell(b).Build();

  CardContributions contributions =
      MakeContributionMaps(player.battlefield.spells);
  double points = PlayTurn(lib, &player, rand, &contributions);
  // Points:
  // + 1/2 points for existing creature
  // + 4/2 points for playing the onetime ability once.
  // - 1/2 points for too many lands.
  EXPECT_NEAR(points, 2);
  EXPECT_NEAR(GetContribution("Foo", &contributions), 2.5);
}
