#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include <memory>
#include <string>

#include "common/ecs/component.h"
#include "common/resources/resource_manager.h"
#include "common/resources/texture.h"

namespace core {
    namespace components {

        class TextureComponent : public common::ecs::Component {
        public:
            TextureComponent(std::string image_name, std::string image_path, bool alpha = false) {
                this->texture = common::resources::ResourceManager::LoadTextureRelative(
                    image_path.c_str(), image_name, /*alpha=*/ alpha
                );
            }
            
            TextureComponent(common::resources::Texture texture) : texture(texture) {}

            std::unique_ptr<Component> clone() const override {
                return std::make_unique<TextureComponent>(texture);
            }

            int getComponentIdInstance() const override {
                return Component::getComponentId<TextureComponent>();
            }

            common::resources::Texture& getTexture() {
                return this->texture;
            }

        private:
            common::resources::Texture texture;
        };

    } // namespace components
} // namespace core

#endif // TEXTURE_COMPONENT_H