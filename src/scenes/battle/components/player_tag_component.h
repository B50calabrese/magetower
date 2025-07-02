#ifndef PLAYER_TAG_COMPONENT_H
#define PLAYER_TAG_COMPONENT_H

#include <memory>

#include "common/ecs/component.h"

namespace scenes {
namespace battle {
namespace components {

/*
 * Indicates the entity is owned by the player.
 */
class PlayerTagComponent : public common::ecs::Component {
 public:
  PlayerTagComponent() {}

  std::unique_ptr<Component> clone() const override {
    return std::make_unique<PlayerTagComponent>();
  }

  int getComponentIdInstance() const override {
    return Component::getComponentId<PlayerTagComponent>();
  }
};
}  // namespace components
}  // namespace battle
}  // namespace scenes

#endif  // PLAYER_TAG_COMPONENT_H