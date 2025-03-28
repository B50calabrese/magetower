#include "engine.h"

namespace common {
    namespace ecs {

        int Engine::number_of_entities = 0;

        Entity& Engine::newEntity() {
            std::shared_ptr<Entity> entity = std::make_shared<Entity>(Engine::number_of_entities++);
            this->entities.push_back(std::move(entity));
            return *(this->entities.back());
        }

        void Engine::runSystems(double delta_time_ms) {
            // Handle all events first beforehand.
            while (!this->event_queue.empty()) {
                std::unique_ptr<Event> event = std::move(this->event_queue.front());
                this->event_queue.pop();

                // Get the listeners for the given event type.
                std::type_index eventTypeIndex = std::type_index(typeid(*event));
                auto listeners = this->event_type_to_listeners_map.find(eventTypeIndex);

                // If we have any listeners to iterate through then do so.
                if (listeners != this->event_type_to_listeners_map.end()) {
                    for (auto& listener : listeners->second) {
                        if (listener->handleEvent(*event, *this))
                            break;
                    }
                }
                else {
                    std::cout << "No event listeners subscribed for event type: " << event->getName() << "\n";
                }
            }

            // Once events are processed then finish.
            for (const auto& system : this->systems) {
                system->process(*this, delta_time_ms);
            }
        }

    } // namespace ecs
} // namespace common