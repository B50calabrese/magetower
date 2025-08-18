#ifndef SCENES_BATTLE_SYSTEMS_ENEMY_TURN_SYSTEM_H_
#define SCENES_BATTLE_SYSTEMS_ENEMY_TURN_SYSTEM_H_

#include "common/ecs/system.h"
#include "scenes/battle/components/turn_state_singleton_component.h"

namespace scenes {
namespace battle {
namespace systems {

class EnemyTurnSystem : public common::ecs::System {
 public:
  EnemyTurnSystem();

  void process(common::ecs::Engine& engine, double delta_time_ms) override;

 private:
  double time_since_turn_start_;
};

}  // namespace systems
}  // namespace battle
}  // namespace scenes

#endif  // SCENES_BATTLE_SYSTEMS_ENEMY_TURN_SYSTEM_H_
