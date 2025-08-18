#include "ui_render_system.h"

#include <memory>

#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "common/resources/resource_manager.h"
#include "common/resources/texture.h"
#include "core/consts.h"
#include "scenes/battle/components/enemy_tag_component.h"
#include "scenes/battle/components/mana_component.h"
#include "scenes/battle/components/player_tag_component.h"

namespace scenes {
namespace battle {
namespace rendersystems {

const glm::vec2 UiRenderSystem::kManaSize = glm::vec2(50.0f);
const glm::vec2 UiRenderSystem::kPlayerManaPosition = glm::vec2(24.0f);
const glm::vec2 UiRenderSystem::kEnemyManaPosition =
    glm::vec2(core::SCREEN_WIDTH - kManaSize.x - 24.0f,
              core::SCREEN_HEIGHT - kManaSize.y - 24.0f);

UiRenderSystem::UiRenderSystem() {
  mana_texture_ = &common::resources::ResourceManager::LoadTexture(
      "assets/battle/ui/mana_texture.png", "mana_texture", /*alpha=*/true);
}

void UiRenderSystem::render(
    common::ecs::Engine& engine,
    std::shared_ptr<common::twod::RendererManager> renderer_manager) {
  for (auto& entity : engine.getEntities()) {
    // If it is the player, render the mana of the player.
    if (entity->hasComponent<components::PlayerTagComponent>()) {
      // Get the mana component of the player entity.
      auto player_mana_component =
          entity->getComponent<components::ManaComponent>();

      glm::vec2 position = kPlayerManaPosition;
      for (int i = 0; i < player_mana_component->getMaxMana(); i++) {
        renderer_manager->getSpriteRenderer()->DrawSprite(
            *mana_texture_, position, kManaSize, 0.0f, glm::vec4(1.0f));
        position.x += kManaSize.x;
      }
    }

    // If it is the enemy, render the mana of the enemy.
    if (entity->hasComponent<components::EnemyTagComponent>()) {
      // Get the mana component of the enemy entity.
      auto enemy_mana_component =
          entity->getComponent<components::ManaComponent>();

      glm::vec2 position = kEnemyManaPosition;
      for (int i = 0; i < enemy_mana_component->getMaxMana(); i++) {
        renderer_manager->getSpriteRenderer()->DrawSprite(
            *mana_texture_, position, kManaSize, 0.0f, glm::vec4(1.0f));
        position.x -= kManaSize.x;
      }
    }
  }

  auto turn_state = engine.getSingletonComponent<components::TurnStateSingletonComponent>();
  std::string turn_text = (turn_state->getCurrentTurn() == components::Turn::kPlayer)
                              ? "Player's Turn"
                              : "Enemy's Turn";
  renderer_manager->getTextRenderer()->RenderText(
      turn_text, glm::vec2(core::HALF_SCREEN_WIDTH - 100.0f, 20.0f), 20.0f,
      core::COLOR_BLACK);
}

}  // namespace rendersystems
}  // namespace battle
}  // namespace scenes