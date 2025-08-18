#include "renderer_manager.h"

#include "common/resources/resource_manager.h"
#include "common/resources/shader.h"

namespace common {
namespace twod {

RendererManager::RendererManager(glm::mat4 projection_matrix) {
  common::resources::Shader sprite_shader =
      common::resources::ResourceManager::LoadShader(
          "src/common/resources/shaders/sprite.vert",
          "src/common/resources/shaders/sprite.frag", "sprite_shader");
  common::resources::Shader text_shader =
      common::resources::ResourceManager::LoadShader(
          "src/common/resources/shaders/font.vert",
          "src/common/resources/shaders/font.frag", "text_shader");
  sprite_renderer_ =
      std::make_shared<SpriteRenderer>(sprite_shader, projection_matrix);
  text_renderer_ =
      std::make_shared<TextRenderer>(text_shader, projection_matrix);
}

}  // namespace twod
}  // namespace common