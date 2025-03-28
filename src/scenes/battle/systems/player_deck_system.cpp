#include "player_deck_system.h"

#include "common/ecs/entity.h"
#include "core/consts.h"
#include "core/components/animation_component.h"
#include "core/components/card_component.h"
#include "scenes/battle/components/in_player_hand_tag_component.h"
#include "scenes/battle/components/player_deck_singleton_component.h"
#include "scenes/battle/events/player_draw_card_start_event.h"
#include "scenes/battle/events/player_hand_update_event.h"

namespace scenes {
    namespace battle {
        namespace systems {

            using common::ecs::Entity;
            using core::components::AnimationComponent;
            using core::components::CardComponent;
            using scenes::battle::components::InPlayerHandTagComponent;
            using scenes::battle::components::PlayerDeckSingletonComponent;
            using scenes::battle::events::PlayerHandUpdateEvent;
            using scenes::battle::events::PlayerDrawCardStartEvent;

            PlayerDeckSystem::PlayerDeckSystem() {
                this->setRequiredComponent<PlayerDeckSingletonComponent>();
            }

            void PlayerDeckSystem::process(common::ecs::Engine& engine, double delta_time_ms) {

            }


            bool PlayerDeckSystem::handleEvent(common::ecs::Event& event, common::ecs::Engine& engine) {
                if (typeid(event) == typeid(PlayerDrawCardStartEvent)) {
                    // If the player is starting to draw a card, initiate the animation and callback.
                    PlayerDeckSingletonComponent* deck_component = engine.getSingletonComponent<PlayerDeckSingletonComponent>();
                    int drawn_card_id = deck_component->drawCard();
                    std::shared_ptr<Entity> card = engine.getEntityFromId(drawn_card_id);
                    card->addComponent<AnimationComponent>(
                        core::PLAYER_DECK_POSITION,
                        core::PLAYER_HAND_CENTER,
                        100.0f
                    );
                    CardComponent* card_component = card->getComponent<CardComponent>();
                    card_component->setIsFaceup(true);
                    card_component->setIsVisible(true);
                    card->getComponent<AnimationComponent>()->setCallbackFunction(
                        [](common::ecs::Engine& engine, int entity_id) {
                            engine.getEntityFromId(entity_id)->addComponent<InPlayerHandTagComponent>();
                            engine.publishEvent(std::make_unique<PlayerHandUpdateEvent>());
                        });
                    card->getComponent<AnimationComponent>()->setAnimationState(AnimationComponent::ANIMATING);
                    return false;
                }
            }

        } // namespace systems
    } // namespace battle
} // namespace scenes