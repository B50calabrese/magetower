#ifndef MAGETOWER_SRC_COMMON_ECS_COMPONENT_H_
#define MAGETOWER_SRC_COMMON_ECS_COMPONENT_H_

#include <memory>

namespace common {
namespace ecs {

// Base class for all components.
class Component {
 public:
  virtual ~Component() = default;

  virtual std::unique_ptr<Component> clone() const = 0;

  // Gets the unique component id for a given component.
  template <typename T>
  static int GetComponentId() {
    static int component_id = next_component_id_++;
    return component_id;
  }

  // Gets the unique component id given an instance of the component.
  virtual int GetComponentIdInstance() const = 0;

 private:
  inline static int next_component_id_ = 0;
};

}  // namespace ecs
}  // namespace common

#endif  // MAGETOWER_SRC_COMMON_ECS_COMPONENT_H_