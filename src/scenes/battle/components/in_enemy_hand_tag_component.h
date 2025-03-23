#ifndef IN_ENEMY_HAND_TAG_COMPONENT_H
#define IN_ENEMY_HAND_TAG_COMPONENT_H

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
            };
        }
    }
}

#endif // IN_ENEMY_HAND_TAG_COMPONENT_H