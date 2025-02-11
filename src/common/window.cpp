#include "window.h"

#include <iostream>

namespace common {

    int Window::init() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        this->window_internal = glfwCreateWindow(this->width, this->height, this->name, NULL, NULL);
        if (this->window_internal == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(this->window_internal);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return -1;
        }
    }

    void Window::start() {
        while (!glfwWindowShouldClose(this->window_internal))
        {
            if (this->main_loop_callback != nullptr) {
                this->main_loop_callback();
            }
            glfwSwapBuffers(this->window_internal);
            glfwPollEvents();
        }

        glfwTerminate();
    }

} // namespace common