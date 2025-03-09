#ifndef SYSTEM_H
#define SYSTEM_H

#include <bitset>

#include "component.h"
#include "entity.h"

namespace common {
    namespace ecs {

        class Engine;

        /* Base class for systems that act on components. */
        class System {
        public:
            virtual ~System() = default;

            // This is the main function that systems need to override to implement 'logic'.
            virtual void process(Engine& engine) = 0;

        private:
            std::bitset<Entity::MAX_NUMBER_COMPONENTS> requiredSignature; // System's required components

        protected: // Make it protected so derived systems can use it
            template<typename T>
            void setRequiredComponent() {
                requiredSignature[Component::getComponentId<T>()] = true;
            }

            const std::bitset<Entity::MAX_NUMBER_COMPONENTS> getRequiredSignature() {
                return this->requiredSignature;
            }
        };

    } // namespace ecs
} // namespace common

#endif // SYSTEM_H