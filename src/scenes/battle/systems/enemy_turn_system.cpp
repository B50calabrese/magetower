#include "enemy_turn_system.h"

#include "common/ecs/engine.h"

namespace scenes {
namespace battle {
namespace systems {

EnemyTurnSystem::EnemyTurnSystem() : time_since_turn_start_(0.0) {}

void EnemyTurnSystem::process(common::ecs::Engine& engine,
                              double delta_time_ms) {
  auto turn_state =
      engine.getSingletonComponent<components::TurnStateSingletonComponent>();
  if (turn_state->getCurrentTurn() != components::Turn::kEnemy) {
    time_since_turn_start_ = 0.0;
    return;
  }

  time_since_turn_start_ += delta_time_ms;
  if (time_since_turn_start_ >= 2000.0) {  // 2 seconds
    turn_state->setCurrentTurn(components::Turn::kPlayer);
    time_since_turn_start_ = 0.0;
  }
}

}  // namespace systems
}  // namespace battle
}  // namespace scenes
