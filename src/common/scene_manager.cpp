#include "common/scene_manager.h"

#include "common/2D/renderer_manager.h"

namespace common {

SceneManager::SceneManager(glm::mat4 projection_matrix)
    : projection_matrix_(projection_matrix),
      current_scene_(nullptr),
      should_close_window_(false) {}

void SceneManager::Init() {
  renderer_manager_ =
      std::make_shared<common::twod::RendererManager>(projection_matrix_);
}

void SceneManager::AddScene(std::shared_ptr<Scene> scene) {
  scene_map_[scene->id()] = scene;
}

void SceneManager::SetCurrentScene(int id) {
  if (current_scene_ != nullptr) {
    current_scene_->UnloadScene();
  }
  current_scene_ = scene_map_[id];
  current_scene_->LoadScene();
}

void SceneManager::Update(double delta_time_ms) {
  if (current_scene_ != nullptr) {
    Scene::UpdateStatus status = current_scene_->Update(delta_time_ms);

    switch (status) {
      case Scene::UpdateStatus::kCloseWindow:
        should_close_window_ = true;
        break;

      case Scene::UpdateStatus::kSwitchScene:
        SetCurrentScene(current_scene_->next_scene_id());
        break;

      default:
        // Default case fall through.
        break;
    }
  }
}

void SceneManager::Display() { current_scene_->Render(renderer_manager_); }

void SceneManager::UpdateWindo(GLFWwindow* window) {
  if (should_close_window_) {
    glfwSetWindowShouldClose(window, true);
  }
}

void SceneManager::ProcessMouseInput(GLFWwindow* window, double x_pos,
                                     double y_pos) {
  current_scene_->ProcessMouseInput(window, x_pos, y_pos);
}

void SceneManager::ProcessMouseClick(GLFWwindow* window, int button, int action,
                                     int mods) {
  current_scene_->ProcessMouseClick(window, button, action, mods);
}

void SceneManager::ProcessKeyInput(GLFWwindow* window, int key, int scancode,
                                   int action, int mod) {
  current_scene_->ProcessKeyInput(window, key, scancode, action, mod);
}

}  // namespace common