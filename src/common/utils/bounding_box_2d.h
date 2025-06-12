#ifndef BOUNDING_BOX_2D_H
#define BOUNDING_BOX_2D_H

#include <glm/vec2.hpp>

namespace common {
namespace utils {
struct BoundingBox2D {
  glm::vec2 bottom_left;
  glm::vec2 size;
};
}  // namespace utils
}  // namespace common

#endif  // BOUNDING_BOX_2D_H