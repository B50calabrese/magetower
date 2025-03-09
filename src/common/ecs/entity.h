#ifndef ENTITY_H
#define ENTITY_H

#include <bitset>
#include <iostream>
#include <map>
#include <memory>
#include <typeindex>

#include "component.h"

namespace common {
    namespace ecs {      

        /* Container of components defined by an id. */
        class Entity {
        public:
            const static int MAX_NUMBER_COMPONENTS = 64;

            using ComponentMap = std::map<std::type_index, std::unique_ptr<Component>>;

            Entity(int id) : id(id) {}

            /*
            * Adds a component by passing in the arguments used to generate the component.
            */
            template<typename T, typename... Args>
            T& addComponent(Args&&... args) {
                // Get the type of the component.
                std::type_index typeIndex = std::type_index(typeid(T));
                if (this->components.count(typeIndex)) {
                    // Component already exists, maybe handle error or just return existing
                    std::cerr << "Component of type already exists on entity " << id << std::endl;
                    return *static_cast<T*>(this->components[typeIndex].get()); // Return existing component
                }
                std::unique_ptr<T> component = std::make_unique<T>(std::forward<Args>(args)...);
                this->components[typeIndex] = std::move(component);
                this->signature[Component::getComponentId<T>()] = true;
                return *static_cast<T*>(this->components[typeIndex].get()); // Return newly created component
            }

            /*
            * Gets the component of a given type.
            */
            template<typename T>
            T* getComponent() const {
                std::type_index typeIndex = std::type_index(typeid(T));
                if (this->components.count(typeIndex)) {
                    return static_cast<T*>(this->components.at(typeIndex).get());
                }
                return nullptr; // Or throw an exception if component is expected
            }

            /*
            * Returns whether or not a component of a given type exists.
            */
            template<typename T>
            bool hasComponent() const {
                std::type_index typeIndex = std::type_index(typeid(T));
                return this->components.count(typeIndex) > 0;
            }

            const std::bitset<MAX_NUMBER_COMPONENTS> getSignature() {
                return this->signature;
            }

        private:
            // Disallow copy and move for simplicity in this example
            Entity(const Entity&) = delete;
            Entity& operator=(const Entity&) = delete;
            Entity(Entity&&) = delete;
            Entity& operator=(Entity&&) = delete;

            int id;
            ComponentMap components;
            std::bitset<MAX_NUMBER_COMPONENTS> signature;
        };
    } // namespace ecs
} // namespace common

#endif // ENTITY_H