#include "window.h"

#include "common/utils/logger.h"

namespace common {

namespace {
constexpr int kGlfwVersionMajor = 3;
constexpr int kGlfwVersionMinor = 3;
}  // namespace

Window::Window(unsigned int width, unsigned int height, const std::string& name)
    : width_(width),
      height_(height),
      name_(name),
      window_internal_(nullptr),
      last_frame_ms_(0.0) {
  scene_manager = std::make_shared<SceneManager>(
      glm::ortho(0.0f, static_cast<float>(width), 0.0f,
                 static_cast<float>(height), -1.0f, 1.0f));
}

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

void Window::framebufferSizeCallback(GLFWwindow* window, int width,
                                     int height) {
  glViewport(0, 0, width, height);
}

int Window::init() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, kGlfwVersionMajor);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, kGlfwVersionMinor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_internal_ =
      glfwCreateWindow(width_, height_, name_.c_str(), NULL, NULL);
  if (window_internal_ == NULL) {
    utils::Logger::Error("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window_internal_);

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
    utils::Logger::Error("Failed to initialize GLAD");
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

  scene_manager->init();
  initCallbacks();
  return 0;
}

void Window::start() {
  while (!glfwWindowShouldClose(window_internal_)) {
    double current_frame = glfwGetTime();
    double delta_time = current_frame - last_frame_ms_;
    last_frame_ms_ = current_frame;

    scene_manager->updateWindow(window_internal_);

    scene_manager->update(last_frame_ms_);

    scene_manager->display();

    glfwSwapBuffers(window_internal_);
    glfwPollEvents();
  }

  glfwTerminate();
}

// Private functions

void Window::initCallbacks() {
  glfwSetWindowUserPointer(window_internal_, reinterpret_cast<void*>(this));
  glfwSetCursorPosCallback(window_internal_, Window::mouseMovementCallback);
  glfwSetMouseButtonCallback(window_internal_, Window::mouseInputCallback);
  glfwSetKeyCallback(window_internal_, Window::keyCallback);
  glfwSetFramebufferSizeCallback(window_internal_,
                                 Window::framebufferSizeCallback);
}

}  // namespace common