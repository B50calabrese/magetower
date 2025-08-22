#ifndef MAGETOWER_SRC_COMMON_WINDOW_H_
#define MAGETOWER_SRC_COMMON_WINDOW_H_

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

#include "common/2D/renderer_manager.h"
#include "common/scene_manager.h"

namespace common {

class Window {
 public:
  Window(unsigned int width, unsigned int height, const std::string& name);

  static void MouseMovementCallback(GLFWwindow* window, double xPos,
                                    double yPos);

  static void MouseInputCallback(GLFWwindow* window, int button, int action,
                                 int mods);

  static void KeyCallback(GLFWwindow* window, int key, int scancode, int action,
                          int mod);

  static void FramebufferSizeCallback(GLFWwindow* window, int width,
                                      int height);

  int Init();

  void Start();

  std::shared_ptr<SceneManager> scene_manager() { return scene_manager_; }

 private:
  void InitCallbacks();

  unsigned int width_;
  unsigned int height_;
  std::string name_;

  GLFWwindow* window_internal_;
  std::shared_ptr<SceneManager> scene_manager_;

  double last_frame_ms_;
};
}  // namespace common

#endif  // MAGETOWER_SRC_COMMON_WINDOW_H_