#ifndef IN_ENEMY_HAND_TAG_COMPONENT_H
#define IN_ENEMY_HAND_TAG_COMPONENT_H

#include <memory>

#include "common/ecs/component.h"

namespace scenes {
namespace battle {
namespace components {

/*
 * Indicates that a card entity is in the enemy's hand.
 */
class InEnemyHandTagComponent : public common::ecs::Component {
 public:
  InEnemyHandTagComponent() = default;

  std::unique_ptr<Component> clone() const override {
    return std::make_unique<InEnemyHandTagComponent>();
  }

  int getComponentIdInstance() const override {
    return Component::getComponentId<InEnemyHandTagComponent>();
  }
};
}  // namespace components
}  // namespace battle
}  // namespace scenes

#endif  // IN_ENEMY_HAND_TAG_COMPONENT_H