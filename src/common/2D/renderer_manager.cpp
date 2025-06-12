#include "renderer_manager.h"

#include "common/resources/resource_manager.h"
#include "common/resources/shader.h"

namespace common {
namespace twod {

using common::resources::ResourceManager;
using common::resources::Shader;

RendererManager::RendererManager(glm::mat4 projection_matrix) {
  Shader sprite_shader = ResourceManager::LoadShaderRelative(
      "src/common/resources/shaders/sprite.vert",
      "src/common/resources/shaders/sprite.frag", "sprite_shader");
  Shader text_shader = ResourceManager::LoadShaderRelative(
      "src/common/resources/shaders/font.vert",
      "src/common/resources/shaders/font.frag", "text_shader");
  this->sprite_renderer =
      std::make_shared<SpriteRenderer>(sprite_shader, projection_matrix);
  this->text_renderer =
      std::make_shared<TextRenderer>(text_shader, projection_matrix);
}

}  // namespace twod
}  // namespace common