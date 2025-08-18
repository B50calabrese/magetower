#ifndef COMMON_WINDOW_H_
#define COMMON_WINDOW_H_

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "2D/renderer_manager.h"
#include "scene_manager.h"

namespace common {

class Window {
 public:
  Window(unsigned int width, unsigned int height, const std::string& name);

  static void mouseMovementCallback(GLFWwindow* window, double xPos,
                                    double yPos);

  static void mouseInputCallback(GLFWwindow* window, int button, int action,
                                 int mods);

  static void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                          int mod);

  static void framebufferSizeCallback(GLFWwindow* window, int width,
                                      int height);

  int init();

  void start();

  std::shared_ptr<SceneManager> getSceneManager() { return scene_manager; }

 private:
  void initCallbacks();

  unsigned int width_;
  unsigned int height_;
  std::string name_;

  GLFWwindow* window_internal_;
  std::shared_ptr<SceneManager> scene_manager;

  double last_frame_ms_;
};
}  // namespace common

#endif  // COMMON_WINDOW_H_