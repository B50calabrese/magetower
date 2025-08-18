#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common/utils/logger.h"
#include "common/window.h"
#include "core/consts.h"
#include "scenes/battle/battle_scene.h"
#include "scenes/mainmenu/main_menu_scene.h"
#include "scenes/map/map_scene.h"
#include "scenes/shop/shop_scene.h"

int main() {
  common::utils::Logger::Init();
  auto window = std::make_unique<common::Window>(
      core::SCREEN_WIDTH, core::SCREEN_HEIGHT, std::string("Mage Tower"));
  window->init();

  // Load the scenes for the game.
  auto scene_manager = window->getSceneManager();

  auto main_menu_scene = std::make_shared<scenes::mainmenu::MainMenuScene>();
  scene_manager->addScene(main_menu_scene);
  scene_manager->setCurrentScene(static_cast<int>(core::SceneId::Map));

  auto battle_scene = std::make_shared<scenes::battle::BattleScene>();
  scene_manager->addScene(battle_scene);

  auto map_scene = std::make_shared<scenes::map::MapScene>();
  scene_manager->addScene(map_scene);

  auto shop_scene = std::make_shared<scenes::shop::ShopScene>();
  scene_manager->addScene(shop_scene);

  window->start();
  return 0;
}