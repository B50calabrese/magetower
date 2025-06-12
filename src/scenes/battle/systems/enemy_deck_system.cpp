#include "enemy_deck_system.h"

#include "common/ecs/entity.h"
#include "core/components/animation_component.h"
#include "core/components/animation_state_component.h"
#include "core/components/card_component.h"
#include "core/consts.h"
#include "scenes/battle/components/enemy_deck_singleton_component.h"
#include "scenes/battle/components/in_enemy_hand_tag_component.h"
#include "scenes/battle/events/enemy_draw_card_start_event.h"
#include "scenes/battle/events/enemy_hand_update_event.h"

namespace scenes {
namespace battle {
namespace systems {

using common::ecs::Entity;
using core::components::AnimationComponent;
using core::components::AnimationStateComponent;
using core::components::CardComponent;
using scenes::battle::components::EnemyDeckSingletonComponent;
using scenes::battle::components::InEnemyHandTagComponent;
using scenes::battle::events::EnemyDrawCardStartEvent;
using scenes::battle::events::EnemyHandUpdateEvent;

EnemyDeckSystem::EnemyDeckSystem() {
  this->setRequiredComponent<EnemyDeckSingletonComponent>();
}

void EnemyDeckSystem::process(common::ecs::Engine& engine,
                              double delta_time_ms) {}

bool EnemyDeckSystem::handleEvent(common::ecs::Event& event,
                                  common::ecs::Engine& engine) {
  AnimationStateComponent* animation_state_component =
      engine.getSingletonComponent<AnimationStateComponent>();
  if (typeid(event) == typeid(EnemyDrawCardStartEvent) &&
      animation_state_component != nullptr &&
      !animation_state_component->isAnimationPlaying()) {
    // If the enemy is starting to draw a card, initiate the animation and
    // callback.
    EnemyDeckSingletonComponent* deck_component =
        engine.getSingletonComponent<EnemyDeckSingletonComponent>();

    // If the enym doesn't have enough cards, consume the event for now.
    if (deck_component->getSizeOfDeck() <= 0) return true;

    int drawn_card_id = deck_component->drawCard();
    std::shared_ptr<Entity> card = engine.getEntityFromId(drawn_card_id);
    card->addComponent<AnimationComponent>(core::ENEMY_DECK_POSITION,
                                           core::ENEMY_HAND_CENTER, 100.0f);
    CardComponent* card_component = card->getComponent<CardComponent>();
    card_component->setIsFaceup(true);
    card_component->setIsVisible(true);
    card->getComponent<AnimationComponent>()->setCallbackFunction(
        [](common::ecs::Engine& engine, int entity_id) {
          engine.getEntityFromId(entity_id)
              ->addComponent<InEnemyHandTagComponent>();
          engine.publishEvent(std::make_unique<EnemyHandUpdateEvent>());
        });
    card->getComponent<AnimationComponent>()->setAnimationState(
        AnimationComponent::ANIMATING);
    return true;
  }
  return false;
}

}  // namespace systems
}  // namespace battle
}  // namespace scenes