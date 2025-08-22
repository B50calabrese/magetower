#ifndef MAGETOWER_SRC_COMMON_SCENE_MANAGER_H_
#define MAGETOWER_SRC_COMMON_SCENE_MANAGER_H_

#include <map>
#include <memory>

#include "glm/mat4x4.hpp"

#include "common/scene.h"

// Forward declaration to avoid including header.
namespace common::twod {
class RendererManager;
}

namespace common {

// Handles the management of various scenes in a game.
class SceneManager {
 public:
  explicit SceneManager(glm::mat4 projection_matrix);

  void Init();
  void AddScene(std::shared_ptr<Scene> scene);
  void SetCurrentScene(int id);
  void Update(double delta_time_ms);
  void Display();
  void UpdateWindo(GLFWwindow* window);
  void ProcessMouseInput(GLFWwindow* window, double x_pos, double y_pos);
  void ProcessMouseClick(GLFWwindow* window, int button, int action, int mods);
  void ProcessKeyInput(GLFWwindow* window, int key, int scancode, int action,
                       int mod);

 private:
  glm::mat4 projection_matrix_;
  std::map<int, std::shared_ptr<Scene>> scene_map_;
  std::shared_ptr<Scene> current_scene_;
  bool should_close_window_;

  std::shared_ptr<common::twod::RendererManager> renderer_manager_;
};
}  // namespace common

#endif  // MAGETOWER_SRC_COMMON_SCENE_MANAGER_H_