#ifndef SPRITE_TAG_COMPONENT_H
#define SPRITE_TAG_COMPONENT_H

#include "common/ecs/component.h"

namespace core {
    namespace components {

        /*
        * Used to signify a 'sprite' on the screen.
        */
        class SpriteTagComponent : public common::ecs::Component{
        public:
            SpriteTagComponent() {}
        };

    } // namespace components
} // namespace core

#endif // SPRITE_TAG_COMPONENT_H