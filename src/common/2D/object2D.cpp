#include "common/2D/object2D.h"

namespace common {
namespace twod {

bool Object2D::ContainsPoint(glm::vec2 point) const {
  bool in_x = (position_.x < point.x) &&
              ((position_.x + (size_.x * scale_.x)) > point.x);
  bool in_y = (position_.y < point.y) &&
              ((position_.y + (size_.y * scale_.y)) > point.y);
  return in_x && in_y;
}

}  // namespace twod
}  // namespace common