#include "turn_state_system.h"

#include "scenes/battle/components/turn_state_singleton_component.h"

namespace scenes::battle::systems {

using scenes::battle::components::TurnStateSingletonComponent;

TurnStateSystem::TurnStateSystem() {
  this->setRequiredComponent<TurnStateSingletonComponent>();
}

void TurnStateSystem::process(common::ecs::Engine& engine,
                              double delta_time_ms) {}

}  // namespace scenes::battle::systems
