#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "2D/renderer_manager.h"
#include "scene_manager.h"

namespace common {

    class Window {
    public:
        Window(unsigned int width, unsigned int height, const char* name) :
            width(width), height(height), name(name), last_frame_ms(0.0f) {
            this->scene_manager = std::make_shared<SceneManager>(
                glm::ortho(0.0f, static_cast<float>(width),
                    0.0f, static_cast<float>(height), -1.0f, 1.0f)
            );
        }

        int init();

        void start();

        std::shared_ptr<SceneManager> getSceneManager() {
            return this->scene_manager;
        }

    private:
        unsigned int width;
        unsigned int height;
        const char* name;

        GLFWwindow* window_internal;
        std::shared_ptr<SceneManager> scene_manager;

        float last_frame_ms;
    };
} // namespace common

#endif // WINDOW_H