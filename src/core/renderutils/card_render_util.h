#ifndef CORE_RENDERUTILS_CARD_RENDER_UTIL_H_
#define CORE_RENDERUTILS_CARD_RENDER_UTIL_H_

#include <memory>

#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "common/resources/texture.h"

namespace core {
namespace renderutils {

/*
 * Utility class for rendering cards/card backs. It encapsulates the positioning
 * of card information, and avoids having multiple references to the same set of
 * card frames/backs.
 */
class CardRenderUtil {
 public:
  CardRenderUtil();

  void renderCard(
      const common::ecs::Entity& entity,
      std::shared_ptr<common::twod::RendererManager> renderer_manager);

  void renderCardBack(
      glm::vec2 position, glm::vec2 size,
      std::shared_ptr<common::twod::RendererManager> renderer_manager);

 private:
  common::resources::Texture* card_back_texture_;
  common::resources::Texture* creature_card_frame_texture_;
  common::resources::Texture* spell_card_frame_texture_;
};

}  // namespace renderutils
}  // namespace core

#endif  // CORE_RENDERUTILS_CARD_RENDER_UTIL_H_