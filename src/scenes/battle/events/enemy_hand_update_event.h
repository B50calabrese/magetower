#ifndef ENEMY_HAND_UPDATE_EVENT_H
#define ENEMY_HAND_UPDATE_EVENT_H

#include <string>

#include "common/ecs/event.h"

namespace scenes {
    namespace battle {
        namespace events {

            class EnemyHandUpdateEvent : public common::ecs::Event {
            public:
                std::string getName() const { return "EnemyHandUpdateEvent"; }
            };

        } // namespace events
    } // namespace battle
} // namespace scenes

#endif // ENEMY_HAND_UPDATE_EVENT_H