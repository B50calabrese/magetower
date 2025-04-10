#ifndef ENEMY_DRAW_CARD_START_EVENT_H
#define ENEMY_DRAW_CARD_START_EVENT_H

#include <string>

#include "common/ecs/event.h"

namespace scenes {
    namespace battle {
        namespace events {

            class EnemyDrawCardStartEvent : public common::ecs::Event {
            public:
                std::string getName() const { return "EnemyDrawCardStartEvent"; }
            };

        } // namespace events
    } // namespace battle
} // namespace scenes

#endif // ENEMY_DRAW_CARD_START_EVENT_H