#include "card_hold_system.h"

#include "common/utils/math.h"
#include "core/consts.h"
#include "core/components/card_component.h"
#include "core/components/mouse_position_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"
#include "core/events/mouse_click_event.h"
#include "scenes/battle/components/input_state_singleton_component.h"
#include "scenes/battle/components/in_player_hand_tag_component.h"
#include "scenes/battle/components/player_holding_card_tag_component.h"
#include "scenes/battle/events/player_hand_update_event.h"

namespace scenes {
    namespace battle {
        namespace systems {

            using core::components::CardComponent;
            using core::components::MousePositionComponent;
            using core::components::PositionComponent;
            using core::components::SizeComponent;
            using core::events::MouseClickEvent;
            using scenes::battle::components::InputStateSingletonComponent;
            using scenes::battle::components::InPlayerHandTagComponent;
            using scenes::battle::components::PlayerHoldingCardTagComponent;
            using scenes::battle::events::PlayerHandUpdateEvent;

            CardHoldSystem::CardHoldSystem() {
                this->setRequiredComponent<CardComponent>();
                this->setRequiredComponent<PositionComponent>();
                this->setRequiredComponent<SizeComponent>();
                this->setRequiredComponent<PlayerHoldingCardTagComponent>();
            }

            void CardHoldSystem::process(common::ecs::Engine& engine, double delta_time_ms) {
                for (auto& entity : engine.getEntities()) {
                    if ((this->getRequiredSignature() & entity->getSignature()) == this->getRequiredSignature()) {
                        SizeComponent* size_component = entity->getComponent<SizeComponent>();
                        size_component->setHeight(core::CARD_HOLDING_HEIGHT);
                        size_component->setWidth(core::CARD_HOLDING_WIDTH);

                        MousePositionComponent* mouse_position = engine.getSingletonComponent<MousePositionComponent>();
                        PositionComponent* position_component = entity->getComponent<PositionComponent>();
                        position_component->setX(mouse_position->getX() - core::CARD_HOLDING_HALF_WIDTH);
                        position_component->setY(mouse_position->getY() - core::CARD_HOLDING_HALF_HEIGHT);
                    }
                }
            }

            bool CardHoldSystem::handleEvent(common::ecs::Event& event, common::ecs::Engine& engine) {
                auto* input_state_component = engine.getSingletonComponent<InputStateSingletonComponent>();

                if (input_state_component->getInputState() == InputStateSingletonComponent::PLAYER_HOLDING_CARD
                    && typeid(event) == typeid(MouseClickEvent)) {
                    for (auto& entity : engine.getEntities()) {
                        if ((this->getRequiredSignature() & entity->getSignature()) == this->getRequiredSignature()) {
                            MousePositionComponent* mouse_position = engine.getSingletonComponent<MousePositionComponent>();

                            if (common::utils::boundingBoxContains(core::BOARD_BOUNDING_BOX, mouse_position->getPosition())) {
                                // Implement a 'play the card' style event.
                                std::cout << "Got it!!\n";
                            }

                            entity->removeComponent<PlayerHoldingCardTagComponent>();
                            entity->addComponent<InPlayerHandTagComponent>();
                            engine.publishEvent(std::make_unique<PlayerHandUpdateEvent>());
                            input_state_component->setInputState(InputStateSingletonComponent::FULL_CONTROL);
                            return true;
                        }
                    }
                }

                return false;
            }

        } // namespace systems
    } // namespace battle
} // namespace scenes