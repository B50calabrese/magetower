#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "common/resources/shader.h"
#include "common/resources/texture.h"

namespace common {
namespace twod {

using common::resources::Shader;
using common::resources::Texture;

class SpriteRenderer {
 public:
  SpriteRenderer(Shader& shader, glm::mat4 projection_matrix);

  void DrawSprite(Texture& texture, glm::vec2 position,
                  glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
                  glm::vec4 color = glm::vec4(1.0f));

  void DrawSprite(Texture& texture, glm::mat4 model_matrix,
                  glm::vec4 color = glm::vec4(1.0f));

 private:
  void init();

  void bindTextureAndDraw(Texture& texture);

  glm::mat4 generateModelMatrix(glm::vec2 position, glm::vec2 size,
                                float rotate);

  Shader shader;
  glm::mat4 projection_matrix;

  unsigned int VAO;
};

}  // namespace twod
}  // namespace common

#endif  // SPRITE_RENDERER_H