#ifndef SCENES_BATTLE_RENDERSYSTEMS_UI_RENDER_SYSTEM_H_
#define SCENES_BATTLE_RENDERSYSTEMS_UI_RENDER_SYSTEM_H_

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
  static const glm::vec2 kPlayerManaPosition;
  static const glm::vec2 kEnemyManaPosition;
  static const glm::vec2 kManaSize;

  common::resources::Texture* mana_texture_;
};
}  // namespace rendersystems
}  // namespace battle
}  // namespace scenes

#endif  // SCENES_BATTLE_RENDERSYSTEMS_UI_RENDER_SYSTEM_H_