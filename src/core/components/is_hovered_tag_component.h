#ifndef IS_HOVERED_TAG_COMPONENT_H
#define SPRITE_TAG_COMPONENT_H

#include <memory>

#include "common/ecs/component.h"

namespace core {
    namespace components {

        /*
        * Used to signify an entity is 'hovered'.
        */
        class IsHoveredTagComponent : public common::ecs::Component {
        public:
            IsHoveredTagComponent() {}

            std::unique_ptr<Component> clone() const override {
                return std::make_unique<IsHoveredTagComponent>();
            }

            int getComponentIdInstance() const override {
                return Component::getComponentId<IsHoveredTagComponent>();
            }
        };

    } // namespace components
} // namespace core

#endif // SPRITE_TAG_COMPONENT_H