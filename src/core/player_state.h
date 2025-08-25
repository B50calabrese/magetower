#ifndef CORE_PLAYER_STATE_H_
#define CORE_PLAYER_STATE_H_

#include <vector>

namespace core {

class PlayerState {
 public:
  PlayerState() : health_(100), money_(0), current_map_level_(0) {}

  int getHealth() const { return health_; }
  void setHealth(int health) { health_ = health; }

  int getMoney() const { return money_; }
  void setMoney(int money) { money_ = money; }

  const std::vector<int>& getDeck() const { return deck_; }
  void addCardToDeck(int card_id) { deck_.push_back(card_id); }

  int getCurrentMapLevel() const { return current_map_level_; }
  void setCurrentMapLevel(int level) { current_map_level_ = level; }

 private:
  int health_;
  int money_;
  std::vector<int> deck_;
  int current_map_level_;
};

}  // namespace core

#endif  // CORE_PLAYER_STATE_H_
