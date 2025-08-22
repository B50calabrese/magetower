#ifndef MAGETOWER_SRC_CORE_COMPONENTS_MOUSE_POSITION_COMPONENT_H_
#define MAGETOWER_SRC_CORE_COMPONENTS_MOUSE_POSITION_COMPONENT_H_

#include <memory>

#include "glm/ext/vector_float2.hpp"

#include "common/ecs/component.h"

namespace core {
namespace components {

class MousePositionComponent : public common::ecs::Component {
 public:
  MousePositionComponent(float x, float y) : x_(x), y_(y) {}

  std::unique_ptr<Component> clone() const override {
    return std::make_unique<MousePositionComponent>(x_, y_);
  }

  int GetComponentIdInstance() const override {
    return Component::GetComponentId<MousePositionComponent>();
  }

  float x() const { return x_; }

  float y() const { return y_; }

  glm::vec2 position() const { return glm::vec2(x_, y_); }

  void set_x(float x) { x_ = x; }

  void set_y(float y) { y_ = y; }

 private:
  float x_, y_;
};

}  // namespace components
}  // namespace core

#endif  // MAGETOWER_SRC_CORE_COMPONENTS_MOUSE_POSITION_COMPONENT_H_