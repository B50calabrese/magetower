#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "scene_manager.h"

namespace common {

    class Window {
    public:
        Window(unsigned int width, unsigned int height, const char* name) :
            width(width), height(height), name(name) {
            this->main_loop_callback = nullptr;
            this->scene_manager = std::make_shared<SceneManager>();
        }

        int init();

        typedef void (*MainLoopCallback)();
        void setMainLoopCallback(MainLoopCallback main_loop_callback) {
            this->main_loop_callback = main_loop_callback;
        }

        void start();

        std::shared_ptr<SceneManager> getSceneManager() {
            return this->scene_manager;
        }

    private:
        unsigned int width;
        unsigned int height;
        const char* name;

        GLFWwindow* window_internal;
        MainLoopCallback main_loop_callback;
        std::shared_ptr<SceneManager> scene_manager;
    };
} // namespace common

#endif // WINDOW_H