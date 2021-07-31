#pragma once

#include "card_logic.h"
#include "collection.h"
#include "library.h"

struct TurnState {
  ManaCost mana_pool;
  ManaCost agg_card_cost;
};

void DrawOne(Player *player) {
  auto &lib = player->library;
  int total_cards = lib.cards.size() + lib.lands.size();
  if (total_cards <= 0) {
    ERROR << "Cannot draw card because the library is empty!\n";
    return;
  }
  int picked = rand() % total_cards;
  // INFO << "Rand pick " << picked << "\n";
  if (picked >= lib.cards.size()) {
    // Picked a land
    picked -= lib.cards.size();
    Land *land = MoveLand(picked, player->library, player->hand);
    INFO << "Drew " << *land << "\n";
  } else {
    // Picked a non-land
    Card *card = MoveCard(picked, player->library, player->hand);
    INFO << "Drew " << *card << "\n";
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

bool IsColorStarved(const ManaCost &mana_pool) {
  if (FindWithDefault(mana_pool, GetFormat().PrimaryColor(), 0) < 1) {
    return true;
  }
  if (FindWithDefault(mana_pool, GetFormat().SecondaryColor(), 0) < 1) {
    return true;
  }
  return false;
}

void ProduceMana(const Deck &battlefield, ManaCost *mana_pool) {
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
    if (IsColorStarved(*mana_pool)) {
      // Either 1. Add colorless mana, OR
      ++(*mana_pool)[Color::Colorless];
      ++(*mana_pool)[Color::Total];
    } else {
      // 2. Add one of each color, but do not increment total mana.
      AddUniversalColor(mana_pool);
    }
  }
}

void ProduceMana(Player *player, TurnState *state) {
  return ProduceMana(player->battlefield, &state->mana_pool);
}

// Idea for color optimization: accumulate grey mana debt! Must be paid before
// end of turn.
bool IsAffordable(const Card &card, const ManaCost &mana_pool) {
  // Loop checks for both Colors, as well as Total mana cost.
  for (const auto &pair : card.cost) {
    Color color = pair.first;
    int cost_amount = pair.second;
    if (FindWithDefault(mana_pool, color, 0) < cost_amount) {
      return false;
    }
  }
  return true;
}

void PayCost(const Card &card, ManaCost *mana_pool) {
  for (const auto &pair : card.cost) {
    Color color = pair.first;
    int cost_amount = pair.second;
    int &pool_amount = (*mana_pool)[color];
    pool_amount -= cost_amount;

    if (pool_amount < 0) {
      ERROR << "Negative pool amount!\n";
    }
  }
}

// Returns number of points from playing this card.
int PlayCard(int i, Player *player, TurnState *state) {
  PayCost(player->hand.cards[i], &state->mana_pool);
  Card *card = MoveCard(i, player->hand, player->battlefield);
  if (card) {
    INFO << "Played " << *card << "\n";
    DrawN(player, DrawFromPlayedCard(*card, *player));
    return PointsFromPlayedCard(*card, *player);
  } else {
    INFO << "Could not play any card!\n";
  }
  return 0;
}

// Returns points from playing this card.
int PlayBestCard(Player *player, TurnState *state) {
  // TODO refine this algorithm more. For now, merely attempts to play the
  // most expensive card available. Instead could use Dynamic Programming to
  // find best solution.

  int pool_size = TotalCost(state->mana_pool);
  auto &cards = player->hand.cards;

  int best_affordable_priority = -1;
  int best_affordable_card = -1;
  int best_affordable_cost = 0;
  for (int i = 0; i < cards.size(); ++i) {
    if (best_affordable_cost == pool_size) {
      // Has already found optimal play.
      break;
    }
    int card_cost = TotalCost(cards[i].cost);
    if (card_cost > pool_size) {
      continue;
    }
    if (!IsAffordable(cards[i], state->mana_pool)) {
      continue;
    }
    if (cards[i].priority == 0 && player->battlefield.cards.size() < 1) {
      // Cannot play secondary spells if there are no creatures!
      continue;
    }
    if (cards[i].priority < best_affordable_priority) {
      continue;
    }
    if (card_cost > best_affordable_cost) {
      best_affordable_card = i;
      best_affordable_cost = card_cost;
      best_affordable_priority = cards[i].priority;
    }
  }
  int points = best_affordable_cost;
  if (best_affordable_card >= 0) {
    points += PlayCard(best_affordable_card, player, state);
  }
  return points;
}

int PlayCards(Player *player, TurnState *state) {
  int sum = 0;
  for (int addition = -1; addition != 0;) {
    addition = PlayBestCard(player, state);
    sum += addition;
  }
  return sum;
}

void AggregateCosts(const Deck &hand, ManaCost *aggregate) {
  for (const Card &card : hand.cards) {
    (*aggregate) += card.cost;
  }
}

std::vector<std::pair<float, Color>> SortNeeds(const ManaCost &agg_card_cost,
                                               const ManaCost &mana_pool) {
  std::vector<std::pair<float, Color>> scores;
  std::vector<Color> covered;
  for (const auto &pair : agg_card_cost) {
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

// First color is most important to add.
std::vector<Color> ManaNeeds(const Player &player,
                             const ManaCost &agg_card_cost,
                             const ManaCost &mana_pool) {
  std::vector<Color> priorities;
  // ManaPreference(player, mana_pool, &priorities);
  for (const auto &pair : SortNeeds(agg_card_cost, mana_pool)) {
    priorities.push_back(pair.second);
  }
  return priorities;
}

// First color is most important to add.
std::vector<Color> ManaNeeds(const Player &player, const TurnState &state) {
  return ManaNeeds(player, state.agg_card_cost, state.mana_pool);
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
  if (needs.empty()) {
    // Play any land if possible... this should be a rare case.
    return 0;
  }
  int non_basic_land = -1;
  auto &lands = hand.lands;
  for (Color color : needs) {
    int wanted_double_land = -1;
    for (int i = 0; i < lands.size(); ++i) {
      if (lands[i].type == LandType::dual &&
          (lands[i].color == color || *lands[i].secondary == color)) {
        wanted_double_land = i;
      } else if (lands[i].color == color) {
        // Found a wanted color of basic land, play that land!
        return i;
      }

      if (lands[i].type != LandType::basic) {
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

// Returns points from played cards.
double PlayLand(Player *player, TurnState *state) {
  const auto &lands = player->hand.lands;
  if (lands.empty()) {
    INFO << "No lands in hand.\n";
    return 0;
  }

  auto needs = ManaNeeds(*player, *state);
  int i = ChooseLand(needs, *player, player->hand, false, state);
  Land *played = nullptr;

  if (lands[i].type == LandType::fetch) {
    // Sacrifice the land, and search for another land instead.
    // The searched land cannot be tapped this turn.
    MoveLand(i, player->hand, player->graveyard);
    int search = ChooseLand(needs, *player, player->library, true, state);
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

  if (played) {
    return PointsFromPlayedLand(*played, *player);
  }

  return 0;
}

// Returns #points.
double PlayTurn(Player *player) {
  TurnState state;

  // Upkeep
  DrawOne(player);
  INFO << "Hand " << player->hand << "\n";
  AggregateCosts(player->hand, &state.agg_card_cost);
  ProduceMana(player, &state);

  // Main phase
  double bonus = PlayLand(player, &state);
  INFO << "Mana " << state.mana_pool << "\n";
  int cards = PlayCards(player, &state);
  if (cards == 0) {
    // If could not play any cards, then minus one point.
    cards = -1;
  }
  return bonus + cards;
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

void BottomOne(Player *player) {
  ManaCost hand_pool;
  ProduceMana(player->hand, &hand_pool);
  ManaCost hand_cost;
  AggregateCosts(player->hand, &hand_cost);

  auto needs = SortNeeds(hand_cost, hand_pool);

  if (player->hand.lands.size() > player->hand.cards.size()) {
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
    const auto &cards = player->hand.cards;
    int worst_card = 0;
    int least_priority = 100;
    for (int i = 0; i < cards.size(); ++i) {
      if (!IsAffordable(cards[i], hand_pool) &&
          cards[i].priority <= least_priority) {
        worst_card = i;
        least_priority = cards[i].priority;
      }
    }
    MoveCard(worst_card, player->hand, player->library);
  }
}

// First Mulligan, n==1. Second mulligan, n==2.
void DrawMulligan(Player *player, const int n) {
  // DrawN(player, 7 - n);
  // TODO: actually draw 7 and return 1 card of choice...
  DrawN(player, 7);
  for (int i = 0; i < n; ++i) {
    BottomOne(player);
    if (player->hand.Size() + i + 1 != 7) {
      ERROR << "After mulligan " << n << ", incorrect hand size "
            << player->hand.Size() << " !\n";
    }
  }
}

Player StartingHand(const Deck &deck, const MulliganStrategy &strategy) {
  Player player;
  player.library = deck;
  DrawN(&player, 7);

  for (int i = 1; i < 7 && strategy(player.hand, i); ++i) {
    INFO << "Mulligan!\n";
    player = Player();
    player.library = deck;
    DrawMulligan(&player, i);
  }

  return player;
}

int BoardPoints(const Player &player) {
  int sum = 0;
  for (const Card &card : player.battlefield.cards) {
    sum += TotalCost(card.cost);
  }
  return sum;
}

double PlayGame(const Deck &deck, const MulliganStrategy &strategy, int turns) {
  INFO << "-- Game start ------------- \n";
  float score = 0.0f;

  Player player = StartingHand(deck, strategy);

  for (int turn = 0; turn < turns; ++turn) {
    INFO << "-- Begin turn " << (turn + 1) << " ------------- \n";
    // score += BoardPoints(player);
    score += PlayTurn(&player);
    // score += (PlayTurn(&player) / (turn + 1));
    // std::cout << "Score at turn " << (turn + 1) << ": " << score << "\n";
  }
  return score;
}

float AverageScore(const Deck &deck, const MulliganStrategy &strategy,
                   int turns, int games) {
  // constexpr int kNumGames = 100;
  // constexpr int kNumGames = 2000;
  // constexpr int kNumGames = 5000;
  float score = 0.0f;
  for (int i = 0; i < games; ++i) {
    score += PlayGame(deck, strategy, turns);
  }
  return score / games;
}
