#ifndef EVENT_H
#define EVENT_H

#include <string>

namespace common {
    namespace ecs {

        /*
        * Used to signal that something happened in the framework, typically to do 'system to world' level notifcations.
        */
        class Event {
        public:
            virtual ~Event() = default;
            
            virtual std::string getName() const { return "Event"; }

            // Used to indicate whether or not an event should be purged on the first pass if an event listerner doesn't consume it.
            virtual bool shouldConsumeOnFirstPass() { return false; }
        };

    } // namespace ecs
} // namespace common

#endif // EVENT_H