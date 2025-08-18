#ifndef CORE_COMPONENTS_TEXTURE_COMPONENT_H_
#define CORE_COMPONENTS_TEXTURE_COMPONENT_H_

#include <memory>
#include <string>

#include "common/ecs/component.h"
#include "common/resources/resource_manager.h"
#include "common/resources/texture.h"

namespace core {
namespace components {

class TextureComponent : public common::ecs::Component {
 public:
  TextureComponent(const std::string& image_name,
                   const std::string& image_path, bool alpha = false) {
    texture_ = common::resources::ResourceManager::LoadTexture(
        image_path, image_name, /*alpha=*/alpha);
  }

  explicit TextureComponent(common::resources::Texture texture)
      : texture_(texture) {}

  std::unique_ptr<Component> clone() const override {
    return std::make_unique<TextureComponent>(texture_);
  }

  int getComponentIdInstance() const override {
    return Component::getComponentId<TextureComponent>();
  }

  common::resources::Texture& getTexture() { return texture_; }

 private:
  common::resources::Texture texture_;
};

}  // namespace components
}  // namespace core

#endif  // CORE_COMPONENTS_TEXTURE_COMPONENT_H_