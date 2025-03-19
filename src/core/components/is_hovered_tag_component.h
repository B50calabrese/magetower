#ifndef IS_HOVERED_TAG_COMPONENT_H
#define SPRITE_TAG_COMPONENT_H

#include "common/ecs/component.h"

namespace core {
    namespace components {

        /*
        * Used to signify an entity is 'hovered'.
        */
        class IsHoveredTagComponent : public common::ecs::Component {
        public:
            IsHoveredTagComponent() {}
        };

    } // namespace components
} // namespace core

#endif // SPRITE_TAG_COMPONENT_H