#include "object2D.h"

namespace common {
namespace twod {

bool Object2D::containsPoint(glm::vec2 point) {
  return (this->position.x < point.x) && (this->position.y < point.y) &&
         ((this->position.x + (this->size.x * this->scale.x)) > point.x) &&
         ((this->position.y + (this->size.y * this->scale.y)) > point.y);
}

}  // namespace twod
}  // namespace common