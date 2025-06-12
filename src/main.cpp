#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common/utils/logger.h"
#include "common/window.h"
#include "core/consts.h"
#include "scenes/battle/battle_scene.h"
#include "scenes/mainmenu/main_menu_scene.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void callback();

using common::Window;
using scenes::battle::BattleScene;
using scenes::mainmenu::MainMenuScene;

int main() {
  common::utils::Logger::Init();
  Window* window =
      new Window(core::SCREEN_WIDTH, core::SCREEN_HEIGHT, "Mage Tower");
  window->init();

  // Load the scenes for the game.
  auto scene_manager = window->getSceneManager();

  std::shared_ptr<MainMenuScene> main_menu_scene =
      std::make_shared<MainMenuScene>();
  scene_manager->addScene(main_menu_scene);
  scene_manager->setCurrentScene(core::MAIN_MENU_SCENE_ID);

  std::shared_ptr<BattleScene> battle_scene = std::make_shared<BattleScene>();
  scene_manager->addScene(battle_scene);

  window->start();
  return 0;
}

void callback() {}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}