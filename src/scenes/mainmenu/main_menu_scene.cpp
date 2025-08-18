#include "main_menu_scene.h"

#include "common/2D/sprite.h"
#include "common/resources/resource_manager.h"
#include "common/resources/texture.h"
#include "core/consts.h"

namespace scenes {
namespace mainmenu {

void MainMenuScene::render(
    std::shared_ptr<common::twod::RendererManager> renderer_manager) {
  auto sprite_renderer = renderer_manager->getSpriteRenderer();
  // Render the background.
  sprite_renderer->DrawSprite(*background_texture_, glm::vec2(0.0f, 0.0f),
                              background_texture_->getSizeVector(), 0.0f,
                              glm::vec4(1.0f));

  // Render the buttons.
  start_button_->render(renderer_manager);
  exit_button_->render(renderer_manager);
}

void MainMenuScene::processMouseClick(GLFWwindow* window, int button,
                                      int action, int mods) {
  // If clicked, check interaction with our buttons on the screen.
  if (wasLeftButtonClicked(button, action)) {
    if (start_button_->containsPoint(mouse_position_)) {
      // Switch scene
      update_status_ = UpdateStatus::kSwitchScene;
      next_scene_id_ = static_cast<int>(core::SceneId::Battle);
    } else if (exit_button_->containsPoint(mouse_position_)) {
      update_status_ = UpdateStatus::kCloseWindow;
    }
  }
}

void MainMenuScene::loadScene() {
  background_texture_ = &common::resources::ResourceManager::LoadTexture(
      "assets/mainmenu/background.png", "main_menu_background", /*alpha=*/true);

  common::resources::Texture& start_button_texture =
      common::resources::ResourceManager::LoadTexture(
          "assets/mainmenu/start_game_button.png", "start_game_button",
          /*alpha=*/true);
  start_button_ = std::make_shared<common::twod::Sprite>(
      start_button_texture,
      glm::vec2(core::HALF_SCREEN_WIDTH - (start_button_texture.getWidth() / 2),
                core::HALF_SCREEN_HEIGHT),
      start_button_texture.getSizeVector());

  common::resources::Texture& exit_button_texture =
      common::resources::ResourceManager::LoadTexture(
          "assets/mainmenu/exit_game_button.png", "exit_game_button",
          /*alpha=*/true);
  exit_button_ = std::make_shared<common::twod::Sprite>(
      exit_button_texture,
      glm::vec2(core::HALF_SCREEN_WIDTH - (exit_button_texture.getWidth() / 2),
                core::HALF_SCREEN_HEIGHT - exit_button_texture.getHeight()),
      exit_button_texture.getSizeVector());
}

}  // namespace mainmenu
}  // namespace scenes