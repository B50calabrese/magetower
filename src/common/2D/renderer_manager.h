#ifndef COMMON_2D_RENDERER_MANAGER_H_
#define COMMON_2D_RENDERER_MANAGER_H_

#include <memory>

#include <glm/mat4x4.hpp>

#include "sprite_renderer.h"
#include "text_renderer.h"

namespace common {
namespace twod {

/*
 * Manages the various types of renderers used throughout a game (i.e. for
 * sprits, text, etc.).
 */
class RendererManager {
 public:
  explicit RendererManager(glm::mat4 projection_matrix);

  std::shared_ptr<SpriteRenderer> getSpriteRenderer() {
    return sprite_renderer_;
  }

  std::shared_ptr<TextRenderer> getTextRenderer() { return text_renderer_; }

 private:
  std::shared_ptr<SpriteRenderer> sprite_renderer_;
  std::shared_ptr<TextRenderer> text_renderer_;
};
}  // namespace twod
}  // namespace common

#endif  // COMMON_2D_RENDERER_MANAGER_H_