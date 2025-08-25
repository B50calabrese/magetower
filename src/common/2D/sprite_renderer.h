#ifndef COMMON_2D_SPRITE_RENDERER_H_
#define COMMON_2D_SPRITE_RENDERER_H_

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "common/resources/shader.h"
#include "common/resources/texture.h"

namespace common {
namespace twod {

class SpriteRenderer {
 public:
  SpriteRenderer(common::resources::Shader shader, glm::mat4 projection_matrix);

  void DrawSprite(const common::resources::Texture& texture, glm::vec2 position,
                  glm::vec2 size, float rotate = 0.0f,
                  glm::vec4 color = glm::vec4(1.0f));

  void DrawSprite(const common::resources::Texture& texture,
                  glm::mat4 model_matrix, glm::vec4 color);

  void DrawLine(glm::vec2 start, glm::vec2 end, float width, glm::vec4 color);

 private:
  void init();

  void bindTextureAndDraw(const common::resources::Texture& texture);

  glm::mat4 generateModelMatrix(glm::vec2 position, glm::vec2 size,
                                float rotate);

  common::resources::Shader shader_;
  glm::mat4 projection_matrix_;

  unsigned int vao_;
};

}  // namespace twod
}  // namespace common

#endif  // COMMON_2D_SPRITE_RENDERER_H_