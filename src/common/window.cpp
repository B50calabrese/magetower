#include "window.h"

#include <iostream>

namespace common {

void Window::mouseMovementCallback(GLFWwindow* window, double xPos,
                                   double yPos) {
  Window* window_internal =
      reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  window_internal->getSceneManager()->processMouseInput(window, xPos, yPos);
}

void Window::mouseInputCallback(GLFWwindow* window, int button, int action,
                                int mods) {
  Window* window_internal =
      reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  window_internal->getSceneManager()->processMouseClick(window, button, action,
                                                        mods);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action,
                         int mod) {
  Window* window_internal =
      reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  window_internal->getSceneManager()->processKeyInput(window, key, scancode,
                                                      action, mod);
}

int Window::init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  this->window_internal =
      glfwCreateWindow(this->width, this->height, this->name, NULL, NULL);
  if (this->window_internal == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(this->window_internal);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_ALWAYS);
  glEnable(GL_STENCIL_TEST);
  glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glStencilFunc(GL_ALWAYS, 1,
                0xFF);  // all fragments should pass the stencil test

  this->scene_manager->init();
  this->initCallbacks();
}

void Window::start() {
  while (!glfwWindowShouldClose(this->window_internal)) {
    double current_frame = glfwGetTime();
    double delta_time = current_frame - this->last_frame_ms;
    this->last_frame_ms = current_frame;

    this->scene_manager->updateWindow(this->window_internal);

    this->scene_manager->update(last_frame_ms);

    this->scene_manager->display();

    glfwSwapBuffers(this->window_internal);
    glfwPollEvents();
  }

  glfwTerminate();
}

// Private functions

void Window::initCallbacks() {
  glfwSetWindowUserPointer(this->window_internal,
                           reinterpret_cast<void*>(this));
  glfwSetCursorPosCallback(this->window_internal,
                           Window::mouseMovementCallback);
  glfwSetMouseButtonCallback(this->window_internal, Window::mouseInputCallback);
  glfwSetKeyCallback(this->window_internal, Window::keyCallback);
}

}  // namespace common