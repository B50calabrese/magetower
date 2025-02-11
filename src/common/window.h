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
        }

        int init();

        typedef void (*MainLoopCallback)();
        void setMainLoopCallback(MainLoopCallback main_loop_callback) {
            this->main_loop_callback = main_loop_callback;
        }

        void start();

    private:
        unsigned int width;
        unsigned int height;
        const char* name;

        GLFWwindow* window_internal;
        MainLoopCallback main_loop_callback;
        SceneManager scene_manager;
    };
} // namespace common

#endif // WINDOW_H