#ifndef MAGETOWER_SRC_SCENES_BATTLE_SYSTEMS_SYSTEM_UTILS_H_
#define MAGETOWER_SRC_SCENES_BATTLE_SYSTEMS_SYSTEM_UTILS_H_

#include "common/utils/bounding_box_2d.h"
#include "core/components/mouse_position_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"

namespace scenes {
namespace battle {
namespace systems {

// Given a MouseComponent, SizeComponent, and PositionComponent, returns whether
// or not the mouse is within the bounding box defined by those components.
bool MouseWithinSizePosition(
    core::components::MousePositionComponent& mouse_position,
    core::components::PositionComponent& position,
    core::components::SizeComponent& size);

bool MouseWithinBoundingBox(
    core::components::MousePositionComponent& mouse_position,
    common::utils::BoundingBox2D bounding_box);

}  // namespace systems
}  // namespace battle
}  // namespace scenes

#endif  // MAGETOWER_SRC_SCENES_BATTLE_SYSTEMS_SYSTEM_UTILS_H_