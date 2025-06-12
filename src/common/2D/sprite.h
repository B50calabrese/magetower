#ifndef SPRITE_H
#define SPRITE_H

#include "common/resources/texture.h"
#include "object2D.h"
#include "renderer_manager.h"

namespace common {
namespace twod {

/*
 * A sprite contains the size, position, and rotation information for a
 * renderable object.
 */
class Sprite : public Object2D {
 public:
  Sprite(common::resources::Texture texture) : texture(texture) {}
  Sprite(common::resources::Texture texture,
         glm::vec2 position = glm::vec2(0.0f), glm::vec2 size = glm::vec2(0.0f),
         glm::vec2 scale = glm::vec2(1.0f))
      : texture(texture), Object2D(position, size, scale) {}

  void setTexture(common::resources::Texture texture) {
    this->texture = texture;
  }

  common::resources::Texture& getTexture() { return this->texture; }

  void render(std::shared_ptr<RendererManager> renderer_manager);

 private:
  common::resources::Texture texture;
};
}  // namespace twod
}  // namespace common

#endif  // SPRITE_H