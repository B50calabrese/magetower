#ifndef MAGETOWER_SRC_CORE_COMPONENTS_POSITION_COMPONENT_H_
#define MAGETOWER_SRC_CORE_COMPONENTS_POSITION_COMPONENT_H_

#include <memory>

#include "glm/vec2.hpp"

#include "common/ecs/component.h"

namespace core {
namespace components {

class PositionComponent : public common::ecs::Component {
 public:
  explicit PositionComponent(glm::vec2 position) : position_(position) {}

  std::unique_ptr<Component> clone() const override {
    return std::make_unique<PositionComponent>(position_);
  }

  int GetComponentIdInstance() const override {
    return Component::GetComponentId<PositionComponent>();
  }

  glm::vec2 position() const { return position_; }

  void set_position(glm::vec2 position) { position_ = position; }

  float x() const { return position_.x; }

  void set_x(float x) { position_.x = x; }

  float y() const { return position_.y; }

  void set_y(float y) { position_.y = y; }

 private:
  glm::vec2 position_;
};

}  // namespace components
}  // namespace core

#endif  // MAGETOWER_SRC_CORE_COMPONENTS_POSITION_COMPONENT_H_