#include "sprite.h"

namespace common {
namespace twod {

Sprite::Sprite(common::resources::Texture texture) : texture_(texture) {}
Sprite::Sprite(common::resources::Texture texture, glm::vec2 position,
               glm::vec2 size, glm::vec2 scale)
    : Object2D(position, size, scale), texture_(texture) {}

void Sprite::render(std::shared_ptr<RendererManager> renderer_manager) {
  renderer_manager->getSpriteRenderer()->DrawSprite(getTexture(), getPosition(),
                                                    getSize());
}

}  // namespace twod
}  // namespace common