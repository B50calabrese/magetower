#include "battle_scene.h"

#include <GLFW/glfw3.h>

#include <glm/ext/vector_float2.hpp>
#include <memory>
#include <vector>

#include "common/2D/renderer_manager.h"
#include "common/ecs/component.h"
#include "common/ecs/entity.h"
#include "core/components/animation_state_component.h"
#include "core/components/card_component.h"
#include "core/components/mouse_position_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"
#include "core/components/sprite_tag_component.h"
#include "core/components/texture_component.h"
#include "core/consts.h"
#include "core/events/mouse_click_event.h"
#include "core/rendersystems/sprite_render_system.h"
#include "core/renderutils/card_render_util.h"
#include "core/systems/animation_system.h"
#include "scenes/battle/components/enemy_deck_singleton_component.h"
#include "scenes/battle/components/enemy_tag_component.h"
#include "scenes/battle/components/in_enemy_hand_tag_component.h"
#include "scenes/battle/components/in_player_hand_tag_component.h"
#include "scenes/battle/components/input_state_singleton_component.h"
#include "scenes/battle/components/mana_component.h"
#include "scenes/battle/components/player_deck_singleton_component.h"
#include "scenes/battle/components/player_tag_component.h"
#include "scenes/battle/events/player_draw_card_start_event.h"
#include "scenes/battle/events/player_hand_update_event.h"
#include "scenes/battle/rendersystems/card_render_system.h"
#include "scenes/battle/rendersystems/deck_render_system.h"
#include "scenes/battle/rendersystems/ui_render_system.h"
#include "scenes/battle/systems/card_hold_system.h"
#include "scenes/battle/systems/enemy_deck_system.h"
#include "scenes/battle/systems/enemy_hand_system.h"
#include "scenes/battle/systems/player_deck_system.h"
#include "scenes/battle/systems/player_hand_system.h"

namespace scenes {
namespace battle {

using common::ecs::Component;
using common::ecs::Entity;
using core::components::AnimationStateComponent;
using core::components::CardComponent;
using core::components::MousePositionComponent;
using core::components::PositionComponent;
using core::components::SizeComponent;
using core::components::SpriteTagComponent;
using core::components::TextureComponent;
using core::events::MouseClickEvent;
using core::rendersystems::SpriteRenderSystem;
using core::renderutils::CardRenderUtil;
using core::systems::AnimationSystem;
using scenes::battle::components::EnemyDeckSingletonComponent;
using scenes::battle::components::EnemyTagComponent;
using scenes::battle::components::InEnemyHandTagComponent;
using scenes::battle::components::InPlayerHandTagComponent;
using scenes::battle::components::InputStateSingletonComponent;
using scenes::battle::components::ManaComponent;
using scenes::battle::components::PlayerDeckSingletonComponent;
using scenes::battle::components::PlayerTagComponent;
using scenes::battle::events::PlayerDrawCardStartEvent;
using scenes::battle::events::PlayerHandUpdateEvent;
using scenes::battle::rendersystems::CardRenderSystem;
using scenes::battle::rendersystems::DeckRenderSystem;
using scenes::battle::rendersystems::UiRenderSystem;
using scenes::battle::systems::CardHoldSystem;
using scenes::battle::systems::EnemyDeckSystem;
using scenes::battle::systems::EnemyHandSystem;
using scenes::battle::systems::PlayerDeckSystem;
using scenes::battle::systems::PlayerHandSystem;

void BattleScene::render(
    std::shared_ptr<common::twod::RendererManager> renderer_manager) {
  this->ecs_engine.runRenderSystems(renderer_manager);
}

void BattleScene::processMouseClick(GLFWwindow* window, int button, int action,
                                    int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    this->ecs_engine.publishEvent(std::make_unique<MouseClickEvent>());
}

void BattleScene::processKeyInput(GLFWwindow* window, int key, int scancode,
                                  int action, int mod) {
  if (key == GLFW_KEY_E && action == GLFW_PRESS) {
    this->ecs_engine.publishEvent(std::make_unique<PlayerDrawCardStartEvent>());
  }
  if (key == GLFW_KEY_W && action == GLFW_PRESS) {
    player_state_->setCurrentMapLevel(player_state_->getCurrentMapLevel() + 1);
    update_status_ = UpdateStatus::kSwitchScene;
    next_scene_id_ = static_cast<int>(core::SceneId::Map);
  }
}

void BattleScene::loadScene() {
  this->loadSystems();
  this->loadRenderSystems();
  this->loadSingletonComponents();
  this->loadEntities();
}

// Private functions

void BattleScene::loadEntities() {
  // Generate an entity to represent the background on the screen.
  Entity& background_entity = this->ecs_engine.newEntity();
  background_entity.addComponent<TextureComponent>(
      "battle_background", "assets/battle/background.png", /*alpha=*/true);
  background_entity.addComponent<SizeComponent>(core::SCREEN_WIDTH,
                                                core::SCREEN_HEIGHT);
  background_entity.addComponent<PositionComponent>(glm::vec2(0.0f));
  background_entity.addComponent<SpriteTagComponent>();

  this->loadPlayerEntity();
  this->loadEnemyEntity();
}

void BattleScene::loadPlayerEntity() {
  Entity& player_entity = this->ecs_engine.newEntity();
  player_entity.addComponent<PlayerTagComponent>();
  player_entity.addComponent<ManaComponent>(1);
  this->loadPlayerDeck();
}

void BattleScene::loadEnemyEntity() {
  Entity& enemy_entity = this->ecs_engine.newEntity();
  enemy_entity.addComponent<EnemyTagComponent>();
  enemy_entity.addComponent<ManaComponent>(1);
  this->loadEnemyDeck();
}

void BattleScene::loadPlayerDeck() {
  // Generate entities to represent the player's deck and then execute draw
  // commands.
  const std::vector<int>& player_deck = player_state_->getDeck();
  if (player_deck.empty()) {
    // Add a default card if the deck is empty.
    player_state_->addCardToDeck(11);
  }

  for (const int id : player_deck) {
    Entity& entity = this->ecs_engine.newEntity();
    std::vector<std::unique_ptr<Component>> components =
        this->card_registry->getCardPrototype(id);
    for (auto& component : components) {
      entity.addComponent(component);
    }
    entity.getComponent<CardComponent>()->setIsVisible(true);
    entity.getComponent<CardComponent>()->setIsFaceup(true);
    entity.addComponent<InPlayerHandTagComponent>();
  }

  ecs_engine.publishEvent(std::make_unique<PlayerHandUpdateEvent>());
}

void BattleScene::loadEnemyDeck() {}

void BattleScene::loadSystems() {
  this->ecs_engine.registerSystem<AnimationSystem>();
  this->ecs_engine.registerSystem<EnemyDeckSystem>();
  this->ecs_engine.registerSystem<PlayerDeckSystem>();
  this->ecs_engine.registerSystem<EnemyHandSystem>();
  this->ecs_engine.registerSystem<PlayerHandSystem>();
  this->ecs_engine.registerSystem<CardHoldSystem>();
}

void BattleScene::loadRenderSystems() {
  std::shared_ptr<CardRenderUtil> card_render_util =
      std::make_shared<CardRenderUtil>();
  this->ecs_engine.registerRenderSystem<SpriteRenderSystem>();
  this->ecs_engine.registerRenderSystem<CardRenderSystem>(card_render_util);
  this->ecs_engine.registerRenderSystem<DeckRenderSystem>(card_render_util);
  this->ecs_engine.registerRenderSystem<UiRenderSystem>();
}

void BattleScene::loadSingletonComponents() {
  this->ecs_engine.registerSingletonComponent<MousePositionComponent>(0.0f,
                                                                      0.0f);
  this->ecs_engine.registerSingletonComponent<InputStateSingletonComponent>();
  this->ecs_engine.registerSingletonComponent<PlayerDeckSingletonComponent>();
  this->ecs_engine.registerSingletonComponent<EnemyDeckSingletonComponent>();
  this->ecs_engine.registerSingletonComponent<AnimationStateComponent>();
}

}  // namespace battle
}  // namespace scenes