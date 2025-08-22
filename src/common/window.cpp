#include "common/window.h"

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
  scene_manager_ = std::make_shared<SceneManager>(
      glm::ortho(0.0f, static_cast<float>(width), 0.0f,
                 static_cast<float>(height), -1.0f, 1.0f));
}

void Window::MouseMovementCallback(GLFWwindow* window, double xPos,
                                   double yPos) {
  Window* window_internal =
      reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  window_internal->scene_manager()->ProcessMouseInput(window, xPos, yPos);
}

void Window::MouseInputCallback(GLFWwindow* window, int button, int action,
                                int mods) {
  Window* window_internal =
      reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  window_internal->scene_manager()->ProcessMouseClick(window, button, action,
                                                        mods);
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action,
                         int mod) {
  Window* window_internal =
      reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
  window_internal->scene_manager()->ProcessKeyInput(window, key, scancode,
                                                      action, mod);
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width,
                                     int height) {
  glViewport(0, 0, width, height);
}

int Window::Init() {
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

  scene_manager_->Init();
  InitCallbacks();
  return 0;
}

void Window::Start() {
  while (!glfwWindowShouldClose(window_internal_)) {
    double current_frame = glfwGetTime();
    double delta_time = current_frame - last_frame_ms_;
    last_frame_ms_ = current_frame;

    scene_manager_->UpdateWindo(window_internal_);

    scene_manager_->Update(last_frame_ms_);

    scene_manager_->Display();

    glfwSwapBuffers(window_internal_);
    glfwPollEvents();
  }

  glfwTerminate();
}

// Private functions

void Window::InitCallbacks() {
  glfwSetWindowUserPointer(window_internal_, reinterpret_cast<void*>(this));
  glfwSetCursorPosCallback(window_internal_, Window::MouseMovementCallback);
  glfwSetMouseButtonCallback(window_internal_, Window::MouseInputCallback);
  glfwSetKeyCallback(window_internal_, Window::KeyCallback);
  glfwSetFramebufferSizeCallback(window_internal_,
                                 Window::FramebufferSizeCallback);
}

}  // namespace common