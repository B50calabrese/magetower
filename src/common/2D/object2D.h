#ifndef COMMON_2D_OBJECT2D_H_
#define COMMON_2D_OBJECT2D_H_

#include "glm/vec2.hpp"

namespace common {
namespace twod {

/*
 * An Object2D represents a generic 'object' with size, position, and rotation.
 */
class Object2D {
 public:
  Object2D()
      : position_(0.0f),
        size_(0.0f),
        scale_(1.0f),
        rotation_radians_(0.0f) {}
  Object2D(glm::vec2 position, glm::vec2 size, glm::vec2 scale)
      : position_(position),
        size_(size),
        scale_(scale),
        rotation_radians_(0.0f) {}

  void setPosition(glm::vec2 position) { position_ = position; }
  glm::vec2 getPosition() const { return position_; }

  void setSize(glm::vec2 size) { size_ = size; }
  glm::vec2 getSize() const { return size_; }

  void setScale(glm::vec2 scale) { scale_ = scale; }
  glm::vec2 getScale() const { return scale_; }

  void setRotationRadians(float radians) { rotation_radians_ = radians; }
  float getRotationRadians() const { return rotation_radians_; }

  bool containsPoint(glm::vec2 point) const;

 private:
  glm::vec2 position_;
  glm::vec2 size_;
  glm::vec2 scale_;
  float rotation_radians_;
};
}  // namespace twod
}  // namespace common

#endif  // COMMON_2D_OBJECT2D_H_