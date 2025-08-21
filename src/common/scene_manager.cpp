#include "scene_manager.h"

#include "2D/renderer_manager.h"

namespace common {

SceneManager::SceneManager(glm::mat4 projection_matrix)
    : projection_matrix_(projection_matrix),
      current_scene_(nullptr),
      should_close_window_(false) {}

void SceneManager::init() {
  renderer_manager_ =
      std::make_shared<common::twod::RendererManager>(projection_matrix_);
}

void SceneManager::addScene(std::shared_ptr<Scene> scene) {
  scene_map_[scene->getId()] = scene;
}

void SceneManager::setCurrentScene(int id) {
  if (current_scene_ != nullptr) {
    current_scene_->unloadScene();
  }
  current_scene_ = scene_map_[id];
  current_scene_->loadScene();
}

void SceneManager::update(double delta_time_ms) {
  if (current_scene_ != nullptr) {
    Scene::UpdateStatus status = current_scene_->update(delta_time_ms);

    switch (status) {
      case Scene::UpdateStatus::kCloseWindow:
        should_close_window_ = true;
        break;

      case Scene::UpdateStatus::kSwitchScene:
        setCurrentScene(current_scene_->getNextSceneId());
        break;

      default:
        // Default case fall through.
        break;
    }
  }
}

void SceneManager::display() { current_scene_->render(renderer_manager_); }

void SceneManager::updateWindow(GLFWwindow* window) {
  if (should_close_window_) {
    glfwSetWindowShouldClose(window, true);
  }
}

void SceneManager::processMouseInput(GLFWwindow* window, double x_pos,
                                     double y_pos) {
  current_scene_->processMouseInput(window, x_pos, y_pos);
}

void SceneManager::processMouseClick(GLFWwindow* window, int button, int action,
                                     int mods) {
  current_scene_->processMouseClick(window, button, action, mods);
}

void SceneManager::processKeyInput(GLFWwindow* window, int key, int scancode,
                                   int action, int mod) {
  current_scene_->processKeyInput(window, key, scancode, action, mod);
}

}  // namespace common