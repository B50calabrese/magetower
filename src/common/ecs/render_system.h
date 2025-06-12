#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <bitset>
#include <memory>

#include "common/2D/renderer_manager.h"
#include "component.h"
#include "entity.h"

namespace common {
namespace ecs {

class Engine;

/* Base class for systems that render based on components. */
class RenderSystem {
 public:
  virtual ~RenderSystem() = default;

  // This is the main function that render systems need to override to draw.
  virtual void render(
      Engine& engine,
      std::shared_ptr<common::twod::RendererManager> renderer_manager) = 0;

 private:
  std::bitset<Entity::MAX_NUMBER_COMPONENTS>
      requiredSignature;  // System's required components

 protected:  // Make it protected so derived systems can use it
  template <typename T>
  void setRequiredComponent() {
    requiredSignature[Component::getComponentId<T>()] = true;
  }

  const std::bitset<Entity::MAX_NUMBER_COMPONENTS> getRequiredSignature() {
    return this->requiredSignature;
  }
};

}  // namespace ecs
}  // namespace common

#endif  // RENDER_SYSTEM_H