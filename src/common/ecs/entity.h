#ifndef MAGETOWER_SRC_COMMON_ECS_ENTITY_H_
#define MAGETOWER_SRC_COMMON_ECS_ENTITY_H_

#include <bitset>
#include <iostream>
#include <map>
#include <memory>
#include <typeindex>

#include "common/ecs/component.h"

namespace common {
namespace ecs {

// Container of components defined by an id.
class Entity {
 public:
  const static int kMaxNumberComponents = 64;

  using ComponentMap = std::map<std::type_index, std::unique_ptr<Component>>;

  explicit Entity(int id) : id_(id) {}

  int id() { return id_; }

  // Adds a component by passing in the arguments used to generate the
  // component.
  template <typename T, typename... Args>
  T& AddComponent(Args&&... args) {
    // Get the type of the component.
    std::type_index typeIndex = std::type_index(typeid(T));
    if (components_.count(typeIndex)) {
      // Component already exists, maybe handle error or just return existing
      std::cerr << "Component of type already exists on entity " << id_
                << std::endl;
      return *static_cast<T*>(
          components_[typeIndex].get());  // Return existing component
    }
    std::unique_ptr<T> component =
        std::make_unique<T>(std::forward<Args>(args)...);
    components_[typeIndex] = std::move(component);
    signature_[Component::GetComponentId<T>()] = true;
    return *static_cast<T*>(
        components_[typeIndex].get());  // Return newly created component
  }

  void AddComponent(std::unique_ptr<Component>& component) {
    std::type_index typeIndex = std::type_index(typeid(*component));
    if (components_.count(typeIndex)) {
      std::cerr << "Component of type already exists on entity " << id_
                << std::endl;
      return;
    }
    signature_[component->GetComponentIdInstance()] = true;
    components_[typeIndex] = std::move(component);
  }

  template <typename T>
  void RemoveComponent() {
    std::type_index typeIndex = std::type_index(typeid(T));
    if (components_.count(typeIndex)) {
      components_.erase(typeIndex);
      signature_[Component::GetComponentId<T>()] =
          false;  // Clear the bit in the signature
    }
  }

  // Gets the component of a given type.
  template <typename T>
  T* GetComponent() const {
    std::type_index typeIndex = std::type_index(typeid(T));
    if (components_.count(typeIndex)) {
      return static_cast<T*>(components_.at(typeIndex).get());
    }
    return nullptr;  // Or throw an exception if component is expected
  }

  // Returns whether or not a component of a given type exists.
  template <typename T>
  bool HasComponent() const {
    std::type_index typeIndex = std::type_index(typeid(T));
    return components_.count(typeIndex) > 0;
  }

  const std::bitset<kMaxNumberComponents> signature() {
    return signature_;
  }

 private:
  // Disallow copy and move for simplicity in this example
  Entity(const Entity&) = delete;
  Entity& operator=(const Entity&) = delete;
  Entity(Entity&&) = delete;
  Entity& operator=(Entity&&) = delete;

  int id_;
  ComponentMap components_;
  std::bitset<kMaxNumberComponents> signature_;
};
}  // namespace ecs
}  // namespace common

#endif  // MAGETOWER_SRC_COMMON_ECS_ENTITY_H_