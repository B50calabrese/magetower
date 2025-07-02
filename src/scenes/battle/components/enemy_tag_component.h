#ifndef ENEMY_TAG_COMPONENT_H
#define ENEMY_TAG_COMPONENT_H

#include <memory>

#include "common/ecs/component.h"

namespace scenes {
namespace battle {
namespace components {

/*
 * Indicates the entity is owned by the enemy.
 */
class EnemyTagComponent : public common::ecs::Component {
 public:
  EnemyTagComponent() {}

  std::unique_ptr<Component> clone() const override {
    return std::make_unique<EnemyTagComponent>();
  }

  int getComponentIdInstance() const override {
    return Component::getComponentId<EnemyTagComponent>();
  }
};
}  // namespace components
}  // namespace battle
}  // namespace scenes

#endif  // ENEMY_TAG_COMPONENT_H