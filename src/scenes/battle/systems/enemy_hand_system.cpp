#include "enemy_hand_system.h"

#include "common/ecs/engine.h"
#include "common/ecs/entity.h"
#include "core/components/card_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"
#include "core/consts.h"
#include "scenes/battle/components/in_enemy_hand_tag_component.h"

namespace scenes {
namespace battle {
namespace systems {

using common::ecs::Engine;
using common::ecs::Entity;
using core::components::CardComponent;
using core::components::PositionComponent;
using core::components::SizeComponent;
using scenes::battle::components::InEnemyHandTagComponent;

EnemyHandSystem::EnemyHandSystem() {
  this->setRequiredComponent<CardComponent>();
  this->setRequiredComponent<PositionComponent>();
  this->setRequiredComponent<SizeComponent>();
  this->setRequiredComponent<InEnemyHandTagComponent>();
}

void EnemyHandSystem::process(Engine& engine, double delta_time_ms) {
  std::vector<std::shared_ptr<Entity>> enemy_hand;
  float total_width = 0;

  for (auto& entity : engine.getEntities()) {
    if (entity->hasComponent<InEnemyHandTagComponent>()) {
      enemy_hand.push_back(entity);
      SizeComponent* size_component = entity->getComponent<SizeComponent>();
      size_component->setSize(core::CARD_IN_HAND_WIDTH,
                              core::CARD_IN_HAND_HEIGHT);

      total_width += size_component->getWidth();
    }
  }

  // Then using the width of the hand we center it on the center of the screen.
  float start_position_x = core::HALF_SCREEN_WIDTH - (total_width / 2);
  float y = core::SCREEN_SIZE.y - core::CARD_IN_HAND_HEIGHT;
  for (auto entity : enemy_hand) {
    PositionComponent* position_component =
        entity->getComponent<PositionComponent>();
    position_component->setX(start_position_x);
    position_component->setY(y);

    entity->getComponent<CardComponent>()->setIsFaceup(false);

    start_position_x += entity->getComponent<SizeComponent>()->getWidth();
  }
}

bool EnemyHandSystem::handleEvent(common::ecs::Event& event,
                                  common::ecs::Engine& engine) {
  return true;
}

}  // namespace systems
}  // namespace battle
}  // namespace scenes