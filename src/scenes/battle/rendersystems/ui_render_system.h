#ifndef UI_RENDER_SYSTEM_H
#define UI_RENDER_SYSTEM_H

#include <memory>

#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "common/ecs/render_system.h"
#include "common/resources/texture.h"

namespace scenes {
namespace battle {
namespace rendersystems {
/*
 * This system is responsible for rendering the game UI, specifically the
 * players' mana
 */
class UiRenderSystem : public common::ecs::RenderSystem {
 public:
  UiRenderSystem();

  void render(common::ecs::Engine& engine,
              std::shared_ptr<common::twod::RendererManager> renderer_manager);

 private:
  const static glm::vec2 PLAYER_MANA_POSITION;
  const static glm::vec2 ENEMY_MANA_POSITION;
  const static glm::vec2 MANA_SIZE;

  common::resources::Texture mana_texture;
};
}  // namespace rendersystems
}  // namespace battle
}  // namespace scenes

#endif  // UI_RENDER_SYSTEM_H