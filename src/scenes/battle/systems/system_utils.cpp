#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include "core/components/mouse_position_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"

namespace scenes {
    namespace battle {
        namespace systems {

            bool mouseWithinSizePosition(
                core::components::MousePositionComponent& mouse_position,
                core::components::PositionComponent& position,
                core::components::SizeComponent& size) {
                return (
                    mouse_position.getX() > position.getX()
                    && mouse_position.getY() > position.getY()
                    && mouse_position.getX() < (position.getX() + size.getWidth())
                    && mouse_position.getY() < (position.getY() + size.getHeight()));
            }

        } // namespace systems
    } // namespace battle
} // namespace scenes

#endif // SYSTEM_UTILS_H