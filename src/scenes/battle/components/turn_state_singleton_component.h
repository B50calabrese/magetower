#ifndef SCENES_BATTLE_COMPONENTS_TURN_STATE_SINGLETON_COMPONENT_H_
#define SCENES_BATTLE_COMPONENTS_TURN_STATE_SINGLETON_COMPONENT_H_

#include "common/ecs/component.h"

namespace scenes {
namespace battle {
namespace components {

enum class Turn { kPlayer, kEnemy };

class TurnStateSingletonComponent : public common::ecs::Component {
 public:
  TurnStateSingletonComponent() : current_turn_(Turn::kPlayer) {}

  Turn getCurrentTurn() const { return current_turn_; }
  void setCurrentTurn(Turn turn) { current_turn_ = turn; }

  std::unique_ptr<Component> clone() const override {
    return std::make_unique<TurnStateSingletonComponent>();
  }

  int getComponentIdInstance() const override {
    return Component::getComponentId<TurnStateSingletonComponent>();
  }

 private:
  Turn current_turn_;
};

}  // namespace components
}  // namespace battle
}  // namespace scenes

#endif  // SCENES_BATTLE_COMPONENTS_TURN_STATE_SINGLETON_COMPONENT_H_
