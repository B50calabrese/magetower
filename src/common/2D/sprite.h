#ifndef COMMON_2D_SPRITE_H_
#define COMMON_2D_SPRITE_H_

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
  explicit Sprite(common::resources::Texture texture);
  Sprite(common::resources::Texture texture,
         glm::vec2 position = glm::vec2(0.0f), glm::vec2 size = glm::vec2(0.0f),
         glm::vec2 scale = glm::vec2(1.0f));

  void setTexture(common::resources::Texture texture) { texture_ = texture; }

  const common::resources::Texture& getTexture() const { return texture_; }

  void render(std::shared_ptr<RendererManager> renderer_manager);

 private:
  common::resources::Texture texture_;
};
}  // namespace twod
}  // namespace common

#endif  // COMMON_2D_SPRITE_H_