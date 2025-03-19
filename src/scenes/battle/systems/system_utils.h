#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include "core/components/mouse_position_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"

namespace scenes {
    namespace battle {
        namespace systems {

            /*
             * Given a MouseComponent, SizeComponent, and PositionComponent, returns whether or not the mouse is within the bounding
             * box defined by those components.
             */
            bool mouseWithinSizePosition(
                core::components::MousePositionComponent& mouse_position,
                core::components::PositionComponent& position,
                core::components::SizeComponent& size);

        } // namespace systems
    } // namespace battle
} // namespace scenes

#endif // SYSTEM_UTILS_H