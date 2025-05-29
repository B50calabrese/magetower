#ifndef SPRITE_TAG_COMPONENT_H
#define SPRITE_TAG_COMPONENT_H

#include <memory>

#include "common/ecs/component.h"

namespace core {
    namespace components {

        /*
        * Used to signify a 'sprite' on the screen.
        */
        class SpriteTagComponent : public common::ecs::Component{
        public:
            SpriteTagComponent() {}

            std::unique_ptr<Component> clone() const override {
                return std::make_unique<SpriteTagComponent>();
            }

            int getComponentIdInstance() const override {
                return Component::getComponentId<SpriteTagComponent>();
            }
        };

    } // namespace components
} // namespace core

#endif // SPRITE_TAG_COMPONENT_H