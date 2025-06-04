#ifndef CREATURE_COMPONENT_H
#define CREATURE_COMPONENT_H

#include <memory>

#include "common/ecs/component.h"

namespace core {
    namespace components {

        /*
        * Defines the general data required of all creature cards.
        */
        class CreatureComponent : public common::ecs::Component {
        public:
            CreatureComponent() {}

            std::unique_ptr<Component> clone() const override {
                return std::make_unique<CreatureComponent>();
            }

            int getComponentIdInstance() const override {
                return Component::getComponentId<CreatureComponent>();
            }

        private:
        };

    } // namespace components
} // namespace core

#endif // CREATURE_COMPONENT_H