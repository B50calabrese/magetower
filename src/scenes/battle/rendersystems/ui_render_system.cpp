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

using common::ecs::Engine;
using common::resources::Texture;
using common::twod::RendererManager;
using scenes::battle::components::EnemyTagComponent;
using scenes::battle::components::ManaComponent;
using scenes::battle::components::PlayerTagComponent;

const glm::vec2 UiRenderSystem::MANA_SIZE = glm::vec2(50.0f);
const glm::vec2 UiRenderSystem::PLAYER_MANA_POSITION = glm::vec2(24.0f);
const glm::vec2 UiRenderSystem::ENEMY_MANA_POSITION =
    glm::vec2(core::SCREEN_WIDTH - MANA_SIZE.x - 24.0f,
              core::SCREEN_HEIGHT - MANA_SIZE.y - 24.0f);

UiRenderSystem::UiRenderSystem() {
  this->mana_texture = common::resources::ResourceManager::LoadTextureRelative(
      "assets/battle/ui/mana_texture.png", "mana_texture", /*alpha=*/true);
}

void UiRenderSystem::render(Engine& engine,
                            std::shared_ptr<RendererManager> renderer_manager) {
  for (auto& entity : engine.getEntities()) {
    // If it is the player, render the mana of the player.
    if (entity->hasComponent<PlayerTagComponent>()) {
      // Get the mana component of the player entity.
      auto player_mana_component = entity->getComponent<ManaComponent>();

      glm::vec2 position = PLAYER_MANA_POSITION;
      for (int i = 0; i < player_mana_component->getMaxMana(); i++) {
        renderer_manager->getSpriteRenderer()->DrawSprite(this->mana_texture,
                                                          position, MANA_SIZE);
        position.x += MANA_SIZE.x;
      }
    }

    // If it is the enemy, render the mana of the enemy.
    if (entity->hasComponent<EnemyTagComponent>()) {
      // Get the mana component of the enemy entity.
      auto enemy_mana_component = entity->getComponent<ManaComponent>();

      glm::vec2 position = ENEMY_MANA_POSITION;
      for (int i = 0; i < enemy_mana_component->getMaxMana(); i++) {
        renderer_manager->getSpriteRenderer()->DrawSprite(this->mana_texture,
                                                          position, MANA_SIZE);
        position.x -= MANA_SIZE.x;
      }
    }
  }
}

}  // namespace rendersystems
}  // namespace battle
}  // namespace scenes