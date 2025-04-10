#ifndef ENGINE_H
#define ENGINE_H

#include <map>
#include <memory>
#include <queue>
#include <typeindex>
#include <vector>

#include "common/2D/renderer_manager.h"
#include "entity.h"
#include "event.h"
#include "event_listener.h"
#include "render_system.h"
#include "system.h"

namespace common {
    namespace ecs {

        /* Manager of the ecs system, handles the coordination of the different parts. */
        class Engine {
        public:
            using EntityList = std::vector<std::shared_ptr<Entity>>;
            using SystemsList = std::vector<std::unique_ptr<System>>;
            using RenderSystemsList = std::vector<std::unique_ptr<RenderSystem>>;
            using EventQueue = std::queue<std::shared_ptr<Event>>;
            using EventListenersList = std::vector<EventListener*>;
            using EventTypeToListenersMap = std::map<std::type_index, EventListenersList>;
            using SingletonComponentMap = std::map<std::type_index, std::unique_ptr<Component>>;

            Engine() = default;
            ~Engine() = default;

            const EntityList& getEntities() const {
                return this->entities;
            }

            const std::shared_ptr<Entity> getEntityFromId(int id) const {
                for (auto entity : this->entities) {
                    if (entity->getId() == id) {
                        return entity;
                    }
                }
                return nullptr;
            }

            Entity& newEntity();

            /*
            * Registers a given system with the given arguments.
            */
            template<typename T, typename... Args>
            void registerSystem(Args&&... args) {
                std::unique_ptr<T> system = std::make_unique<T>(std::forward<Args>(args)...);
                this->systems.push_back(std::move(system));
                this->systems.back()->registerEventListeners(*this);
            }

            /*
            * Registers a given render system with the given arguments.
            */
            template<typename T, typename... Args>
            void registerRenderSystem(Args&&... args) {
                std::unique_ptr<T> system = std::make_unique<T>(std::forward<Args>(args)...);
                this->render_systems.push_back(std::move(system));
            }

            void runSystems(double delta_time_ms);

            void runRenderSystems(std::shared_ptr<common::twod::RendererManager> renderer_manager) {
                for (const auto& system : this->render_systems) {
                    system->render(*this, renderer_manager);
                }
            }

            void publishEvent(std::unique_ptr<Event> event) {
                this->event_queue.push(std::move(event));
            }

            /*
            * Used to register an event listener, using the event as a template type.
            */
            template<typename EventType>
            void registerEventListener(EventListener* event_listener) {
                std::type_index eventTypeIndex = std::type_index(typeid(EventType));
                this->event_type_to_listeners_map[eventTypeIndex].push_back(event_listener);
            }

            /*
            * Registers a singleton component in the world.
            */
            template<typename T, typename... Args>
            T& registerSingletonComponent(Args&&... args) {
                std::type_index typeIndex = std::type_index(typeid(T));
                if (singleton_component_map.count(typeIndex)) {
                    std::cout << "Singleton Component of type already registered: " << typeIndex.name() << std::endl;
                    return *static_cast<T*>(singleton_component_map[typeIndex].get());
                }
                std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(args)...);
                singleton_component_map[typeIndex] = std::move(component);
                return *static_cast<T*>(singleton_component_map[typeIndex].get());
            }

            /*
            * Return the singleton component registered in the world.
            */
            template<typename T>
            T* getSingletonComponent() const {
                std::type_index typeIndex = std::type_index(typeid(T));
                if (singleton_component_map.count(typeIndex)) {
                    return static_cast<T*>(singleton_component_map.at(typeIndex).get());
                }
                return nullptr; // Return nullptr if singleton component is not registered
            }

        private:
            static int number_of_entities;

            EntityList entities;
            SystemsList systems;
            RenderSystemsList render_systems;
            EventQueue event_queue;
            EventTypeToListenersMap event_type_to_listeners_map;
            SingletonComponentMap singleton_component_map;
        };

    } // namespace ecs
} // namespace common

#endif // ENGINE_H