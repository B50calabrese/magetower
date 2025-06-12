#include "scene_manager.h"

namespace common {

void SceneManager::update(double deltaTimeMs) {
  if (this->current_scene != nullptr) {
    Scene::UpdateStatus status = this->current_scene->update(deltaTimeMs);

    switch (status) {
      case Scene::UpdateStatus::CLOSE_WINDOW:
        this->should_close_window = true;
        break;

      case Scene::UpdateStatus::SWITCH_SCENE:
        this->setCurrentScene(this->current_scene->getNextSceneId());
        break;

      default:
        // Default case fall through.
        break;
    }
  }
}

void SceneManager::display() {
  this->current_scene->render(this->renderer_manager);
}

void SceneManager::updateWindow(GLFWwindow* window) {
  if (this->should_close_window) glfwSetWindowShouldClose(window, true);
}

void SceneManager::processMouseInput(GLFWwindow* window, double xPos,
                                     double yPos) {
  this->current_scene->processMouseInput(window, xPos, yPos);
}

void SceneManager::processMouseClick(GLFWwindow* window, int button, int action,
                                     int mods) {
  this->current_scene->processMouseClick(window, button, action, mods);
}

void SceneManager::processKeyInput(GLFWwindow* window, int key, int scancode,
                                   int action, int mod) {
  this->current_scene->processKeyInput(window, key, scancode, action, mod);
}

}  // namespace common