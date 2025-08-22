#ifndef COMMON_ECS_COMPONENT_H_
#define COMMON_ECS_COMPONENT_H_

#include <memory>

namespace common {
namespace ecs {

/* Base class for all components. */
class Component {
 public:
  virtual ~Component() = default;

  virtual std::unique_ptr<Component> clone() const = 0;

  /*
   * Gets the unique component id for a given component.
   */
  template <typename T>
  static int getComponentId() {
    static int component_id = kNextComponentId++;
    return component_id;
  }

  /*
   * Gets the unique component id given an instance of the component.
   */
  virtual int getComponentIdInstance() const = 0;

 private:
  inline static int kNextComponentId = 0;
};

}  // namespace ecs
}  // namespace common

#endif  // COMMON_ECS_COMPONENT_H_