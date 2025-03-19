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
            /*
            * Handles the given event and returns true if the event should be 'consumed'.
            */
            virtual bool handleEvent(Event& event, Engine& engine) = 0;
        };

    }
}

#endif // EVENT_LISTENER_H