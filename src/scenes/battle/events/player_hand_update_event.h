#ifndef PLAYER_HAND_UPDATE_EVENT_H
#define PLAYER_HAND_UPDATE_EVENT_H

#include <string>

#include "common/ecs/event.h"

namespace scenes {
    namespace battle {
        namespace events {

            class PlayerHandUpdateEvent : public common::ecs::Event {
            public:
                std::string getName() const { return "PlayerHandUpdateEvent"; }
            };

        } // namespace events
    } // namespace battle
} // namespace scenes

#endif // PLAYER_HAND_UPDATE_EVENT_H