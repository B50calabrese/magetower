#ifndef PLAYER_DRAW_CARD_START_EVENT_H
#define PLAYER_DRAW_CARD_START_EVENT_H

#include <string>

#include "common/ecs/event.h"

namespace scenes {
    namespace battle {
        namespace events {

            class PlayerDrawCardStartEvent : public common::ecs::Event {
            public:
                std::string getName() const { return "PlayerDrawCardStartEvent"; }
            };

        } // namespace events
    } // namespace battle
} // namespace scenes

#endif // PLAYER_DRAW_CARD_START_EVENT_H