#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include "event.h"

namespace common {
    namespace ecs {

        class Engine;

        /*
        * Used to hold the logic when an event is triggered.
        */
        class EventListener {
        public:
            virtual void handleEvent(Event& event, Engine& engine) = 0;
        };

    }
}

#endif // EVENT_LISTENER_H