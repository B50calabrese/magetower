#ifndef PLAYER_HOLDING_CARD_TAG_COMPONENT_H
#define PLAYER_HOLDING_CARD_TAG_COMPONENT_H

#include <memory>

#include "common/ecs/component.h"

namespace scenes {
    namespace battle {
        namespace components {

            /*
            * Indicates that a card is being held by the player.
            */
            class PlayerHoldingCardTagComponent : public common::ecs::Component {
            public:
                PlayerHoldingCardTagComponent() = default;

                std::unique_ptr<Component> clone() const override {
                    return std::make_unique<PlayerHoldingCardTagComponent>();
                }

                int getComponentIdInstance() const override {
                    return Component::getComponentId<PlayerHoldingCardTagComponent>();
                }
            };
        }
    }
}

#endif // PLAYER_HOLDING_CARD_TAG_COMPONENT_H