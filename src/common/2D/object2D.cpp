#include "object2D.h"

namespace common {
namespace twod {

bool Object2D::containsPoint(glm::vec2 point) const {
  return (position_.x < point.x) && (position_.y < point.y) &&
         ((position_.x + (size_.x * scale_.x)) > point.x) &&
         ((position_.y + (size_.y * scale_.y)) > point.y);
}

}  // namespace twod
}  // namespace common