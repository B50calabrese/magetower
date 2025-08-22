#include "scenes/battle/systems/system_utils.h"

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

bool MouseWithinSizePosition(MousePositionComponent& mouse_position,
                             PositionComponent& position, SizeComponent& size) {
  return (mouse_position.x() > position.x() &&
          mouse_position.y() > position.y() &&
          mouse_position.x() < (position.x() + size.width()) &&
          mouse_position.y() < (position.y() + size.height()));
}

bool MouseWithinBoundingBox(MousePositionComponent& mouse_position,
                            BoundingBox2D bounding_box) {
  return common::utils::BoundingBoxContains(bounding_box,
                                            mouse_position.position());
}

}  // namespace systems
}  // namespace battle
}  // namespace scenes