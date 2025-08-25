#ifndef COMMON_SCENE_MANAGER_H_
#define COMMON_SCENE_MANAGER_H_

#include <map>
#include <memory>

#include <glm/mat4x4.hpp>

#include "core/player_state.h"
#include "scene.h"

// Forward declaration to avoid including header.
namespace common::twod {
class RendererManager;
}

namespace common {

/**
 * Handles the management of various scenes in a game.
 */
class SceneManager {
 public:
  explicit SceneManager(glm::mat4 projection_matrix);

  void init();
  void addScene(std::shared_ptr<Scene> scene);
  void setCurrentScene(int id);
  void update(double delta_time_ms);
  void display();
  void updateWindow(GLFWwindow* window);
  void processMouseInput(GLFWwindow* window, double x_pos, double y_pos);
  void processMouseClick(GLFWwindow* window, int button, int action, int mods);
  void processKeyInput(GLFWwindow* window, int key, int scancode, int action,
                       int mod);

 private:
  glm::mat4 projection_matrix_;
  std::map<int, std::shared_ptr<Scene>> scene_map_;
  std::shared_ptr<Scene> current_scene_;
  bool should_close_window_;
  std::shared_ptr<core::PlayerState> player_state_;

  std::shared_ptr<common::twod::RendererManager> renderer_manager_;
};
}  // namespace common

#endif  // COMMON_SCENE_MANAGER_H_