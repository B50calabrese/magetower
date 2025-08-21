#ifndef TURN_STATE_SYSTEM_H
#define TURN_STATE_SYSTEM_H

#include "common/ecs/engine.h"
#include "common/ecs/system.h"

namespace scenes::battle::systems {

class TurnStateSystem : public common::ecs::System {
 public:
  TurnStateSystem();

  void process(common::ecs::Engine& engine, double delta_time_ms);
};

}  // namespace scenes::battle::systems

#endif  // TURN_STATE_SYSTEM_H