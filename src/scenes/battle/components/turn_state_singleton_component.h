#ifndef TURN_STATE_SINGLETON_COMPONENT_H
#define TURN_STATE_SINGLETON_COMPONENT_H

#include <memory>
#include <vector>

#include "common/ecs/component.h"
#include "common/ecs/entity.h"

namespace scenes::battle::components {

/*
 * Contains reference to the turn state.
 */
class TurnStateSingletonComponent : public common::ecs::Component {
 public:
  TurnStateSingletonComponent() : is_player_turn(true) {}

  std::unique_ptr<Component> clone() const override {
    return std::make_unique<TurnStateSingletonComponent>();
  }

  int getComponentIdInstance() const override {
    return Component::getComponentId<TurnStateSingletonComponent>();
  }

  bool isPlayerTurn() { return this->is_player_turn; }

  void setIsPlayerTurn(bool is_player_turn) {
    this->is_player_turn = is_player_turn;
  }

  void toggerIsPlayerTurn() { this->is_player_turn = !this->is_player_turn; }

 private:
  bool is_player_turn;
};
}  // namespace scenes::battle::components

#endif  // TURN_STATE_SINGLETON_COMPONENT_H
