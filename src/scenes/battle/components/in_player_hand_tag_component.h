#ifndef IN_PLAYER_HAND_TAG_COMPONENT_H
#define IN_PLAYER_HAND_TAG_COMPONENT_H

#include "common/ecs/component.h"

namespace scenes {
    namespace battle {
        namespace components {

            /*
            * Indicates that a card entity is in the player's hand.
            */
            class InPlayerHandTagComponent : public common::ecs::Component {
            public:
                InPlayerHandTagComponent() = default;
            };
        }
    }
}

#endif // IN_PLAYER_HAND_TAG_COMPONENT_H