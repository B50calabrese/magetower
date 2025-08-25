#ifndef COMMON_SCENE_H_
#define COMMON_SCENE_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <memory>

#include "common/2D/renderer_manager.h"
#include "core/player_state.h"

namespace common {

/**
 * Represents a single 'screen' of a game. The business and rendering logic
 * should be encapsulated in this individual scene.
 */
class Scene {
 public:
  explicit Scene(int id) : id_(id), mouse_position_(0.0f), next_scene_id_(0) {}

  enum UpdateStatus { kOk, kCloseWindow, kSwitchScene };

  virtual void render(
      std::shared_ptr<common::twod::RendererManager> renderer_manager) = 0;
  virtual UpdateStatus update(double delta_time_ms) = 0;
  virtual void processMouseInput(GLFWwindow* window, double x_pos,
                                 double y_pos) = 0;
  virtual void processMouseClick(GLFWwindow* window, int button, int action,
                                 int mods) = 0;
  virtual void processKeyInput(GLFWwindow* window, int key, int scancode,
                               int action, int mod) = 0;
  virtual void loadScene() = 0;
  virtual void unloadScene() = 0;

  void setPlayerState(std::shared_ptr<core::PlayerState> player_state) {
    player_state_ = player_state;
  }

  int getId() const { return id_; }

  int getNextSceneId() const { return next_scene_id_; }

 protected:
  bool wasLeftButtonClicked(const int button, const int action) {
    return (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);
  }

  glm::vec2 convertMousePositionIntoScreenCoordinates(double x_pos,
                                                      double y_pos,
                                                      float screen_width,
                                                      float screen_height) {
    return glm::vec2(x_pos, screen_height - y_pos);
  }

  glm::vec2 mouse_position_;
  int next_scene_id_;
  std::shared_ptr<core::PlayerState> player_state_;

 private:
  int id_;
};

}  // namespace common

#endif  // COMMON_SCENE_H_