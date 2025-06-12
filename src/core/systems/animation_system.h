#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

#include "common/ecs/system.h"

namespace core {
namespace systems {

/*
 * This system is responsible for managing animating entities.
 */
class AnimationSystem : public common::ecs::System {
 public:
  AnimationSystem();

  void process(common::ecs::Engine& engine, double delta_time_ms);
};

}  // namespace systems
}  // namespace core

#endif  // ANIMATION_SYSTEM_H