#include "player_hand_system.h"

#include <memory>
#include <vector>

#include "system_utils.h"
#include "common/ecs/engine.h"
#include "common/ecs/entity.h"
#include "core/consts.h"
#include "core/components/card_component.h"
#include "core/components/is_hovered_tag_component.h"
#include "core/components/mouse_position_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"
#include "core/events/mouse_click_event.h"
#include "scenes/battle/components/in_player_hand_tag_component.h"
#include "scenes/battle/components/input_state_singleton_component.h"
#include "scenes/battle/components/player_holding_card_tag_component.h"
#include "scenes/battle/events/player_hand_update_event.h"

namespace scenes {
    namespace battle {
        namespace systems {

            using common::ecs::Engine;
            using common::ecs::Entity;
            using common::ecs::Event;
            using core::components::CardComponent;
            using core::components::IsHoveredTagComponent;
            using core::components::MousePositionComponent;
            using core::components::PositionComponent;
            using core::components::SizeComponent;
            using core::events::MouseClickEvent;
            using scenes::battle::components::InPlayerHandTagComponent;
            using scenes::battle::components::InputStateSingletonComponent;
            using scenes::battle::components::PlayerHoldingCardTagComponent;
            using scenes::battle::events::PlayerHandUpdateEvent;

            const int PlayerHandSystem::SCALE_SPEED_WIDTH = (core::CARD_IN_HAND_ZOOM_WIDTH - core::CARD_IN_HAND_WIDTH) / 5;
            const int PlayerHandSystem::SCALE_SPEED_HEIGHT = (core::CARD_IN_HAND_ZOOM_HEIGHT - core::CARD_IN_HAND_HEIGHT) / 5;

            PlayerHandSystem::PlayerHandSystem() {
                this->setRequiredComponent<CardComponent>();
                this->setRequiredComponent<PositionComponent>();
                this->setRequiredComponent<SizeComponent>();
                this->setRequiredComponent<InPlayerHandTagComponent>();
            }

            void PlayerHandSystem::process(Engine& engine, double delta_time_ms) {
                MousePositionComponent* mouse_position_component = engine.getSingletonComponent<MousePositionComponent>();
\
                bool needs_update = false;
                for (auto& entity : engine.getEntities()) {
                    if ((this->getRequiredSignature() & entity->getSignature()) == this->getRequiredSignature()) {
                        // First grab the components we care about.
                        SizeComponent* size_component = entity->getComponent<SizeComponent>();
                        PositionComponent* position_component = entity->getComponent<PositionComponent>();

                        if (mouseWithinSizePosition(*mouse_position_component, *position_component, *size_component)) {
                            if (!entity->hasComponent<IsHoveredTagComponent>()) {
                                entity->addComponent<IsHoveredTagComponent>();
                                needs_update = true;
                            }
                            else if (size_component->getWidth() < core::CARD_IN_HAND_ZOOM_WIDTH || size_component->getHeight() < core::CARD_IN_HAND_ZOOM_HEIGHT) {
                                needs_update = true;
                            }
                        }
                        else {
                            if (entity->hasComponent<IsHoveredTagComponent>()) {
                                entity->removeComponent<IsHoveredTagComponent>();
                                needs_update = true;
                            }
                            else if (size_component->getWidth() > core::CARD_IN_HAND_WIDTH || size_component->getHeight() > core::CARD_IN_HAND_HEIGHT) {
                                needs_update = true;
                            }
                        }
                    }
                }

                if (needs_update) {
                    this->updateHandSizeAndPosition(engine);
                }
            }

            bool PlayerHandSystem::handleEvent(Event& event, Engine& engine) {
                if (typeid(event) == typeid(PlayerHandUpdateEvent)) {
                    this->updateHandSizeAndPosition(engine);
                    return true;
                }
                else if (typeid(event) == typeid(MouseClickEvent)) {
                    if (engine.getSingletonComponent<InputStateSingletonComponent>()->getInputState() == InputStateSingletonComponent::FULL_CONTROL) {
                        return this->handlePlayerClickedEvent(engine);
                    }
                }
                return false;
            }

            // Private functions

            void PlayerHandSystem::updateHandSizeAndPosition(common::ecs::Engine& engine) {
                // Calculate the player's hand and the width of the hand
                std::vector<std::shared_ptr<Entity>> player_hand;
                float total_width = 0;

                for (auto& entity : engine.getEntities()) {
                    if (entity->hasComponent<InPlayerHandTagComponent>()) {
                        player_hand.push_back(entity);

                        // On the first path we know the size of the cards.
                        bool is_zoomed = entity->hasComponent<IsHoveredTagComponent>();
                        SizeComponent* size_component = entity->getComponent<SizeComponent>();

                        int width = 0;
                        int height = 0;
                        if (is_zoomed) {
                            width = std::min(
                                core::CARD_IN_HAND_ZOOM_WIDTH,
                                size_component->getWidth() + PlayerHandSystem::SCALE_SPEED_WIDTH);
                            height = std::min(
                                core::CARD_IN_HAND_ZOOM_HEIGHT,
                                size_component->getHeight() + PlayerHandSystem::SCALE_SPEED_HEIGHT);
                        }
                        else {
                            width = std::max(
                                core::CARD_IN_HAND_WIDTH,
                                size_component->getWidth() - PlayerHandSystem::SCALE_SPEED_WIDTH);
                            height = std::max(
                                core::CARD_IN_HAND_HEIGHT,
                                size_component->getHeight() - PlayerHandSystem::SCALE_SPEED_HEIGHT);
                            size_component->setSize(width, height);
                        }
                        size_component->setSize(width, height);

                        total_width += size_component->getWidth();
                    }
                }

                // Then using the width of the hand we center it on the center of the screen.
                float start_position_x = core::PLAYER_HAND_CENTER.x - (total_width / 2);
                for (auto entity : player_hand) {
                    PositionComponent* position_component = entity->getComponent<PositionComponent>();
                    position_component->setX(start_position_x);
                    position_component->setY(0);
                    
                    entity->getComponent<CardComponent>()->setIsVisible(true);

                    start_position_x += entity->getComponent<SizeComponent>()->getWidth();
                }
            }

            bool PlayerHandSystem::handlePlayerClickedEvent(common::ecs::Engine & engine) {
                auto* input_state_component = engine.getSingletonComponent<InputStateSingletonComponent>();
                if (!input_state_component->getInputState() == InputStateSingletonComponent::FULL_CONTROL) {
                    return false;
                }

                MousePositionComponent* mouse_component = engine.getSingletonComponent<MousePositionComponent>();

                // Check that the player is clicking within the player's bounding box, otherwise end early.
                if (mouseWithinBoundingBox(*mouse_component, core::PLAYER_HAND_BOUNDING_BOX)) {
                    for (auto& entity : engine.getEntities()) {
                        if (entity->hasComponent<InPlayerHandTagComponent>()) {
                            if (mouseWithinSizePosition(
                                *mouse_component,
                                *entity->getComponent<PositionComponent>(),
                                *entity->getComponent<SizeComponent>())) {
                                // The user is attempting to pick up card in their hand.
                                input_state_component->setInputState(InputStateSingletonComponent::PLAYER_HOLDING_CARD);
                                entity->removeComponent<InPlayerHandTagComponent>();
                                entity->addComponent< PlayerHoldingCardTagComponent>();
                                this->updateHandSizeAndPosition(engine);
                                return true;
                            }
                        }
                    }
                }
                
                return false;
            }

        } // namespace systems
    } // namespace battle
} // namespace scenes