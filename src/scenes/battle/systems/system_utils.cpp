#ifndef SYSTEM_UTILS_H
#define SYSTEM_UTILS_H

#include "common/utils/bounding_box_2d.h"
#include "common/utils/math.h"
#include "core/components/mouse_position_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"

namespace scenes {
namespace battle {
namespace systems {

using common::utils::BoundingBox2D;
using core::components::MousePositionComponent;
using core::components::PositionComponent;
using core::components::SizeComponent;

bool mouseWithinSizePosition(MousePositionComponent& mouse_position,
                             PositionComponent& position, SizeComponent& size) {
  return (mouse_position.getX() > position.getX() &&
          mouse_position.getY() > position.getY() &&
          mouse_position.getX() < (position.getX() + size.getWidth()) &&
          mouse_position.getY() < (position.getY() + size.getHeight()));
}

bool mouseWithinBoundingBox(MousePositionComponent& mouse_position,
                            BoundingBox2D bounding_box) {
  return common::utils::boundingBoxContains(bounding_box,
                                            mouse_position.getPosition());
}

}  // namespace systems
}  // namespace battle
}  // namespace scenes

#endif  // SYSTEM_UTILS_H