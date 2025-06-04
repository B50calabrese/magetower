#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <map>
#include <memory>

#include "scene.h"

namespace common::twod {
    // Forward declaration to avoid including header.
    class RendererManager;
} // namespace common::twod

namespace common {
    
    /**
    * Handles the management of various scenes in a game.
    */
    class SceneManager {
    public:
        SceneManager(glm::mat4 projection_matrix) : projection_matrix(projection_matrix), should_close_window(false) {}

        void init() {
            this->renderer_manager = std::make_shared<common::twod::RendererManager>(projection_matrix);
        }

        void addScene(std::shared_ptr<Scene> scene) {
            scene_map[scene->getId()] = scene;
        }

        void setCurrentScene(int id) {
            if (this->current_scene != nullptr) {
                this->current_scene->unloadScene();
            }
            this->current_scene = scene_map[id];
            this->current_scene->loadScene();
        }

        void update(double deltaTimeMs);
        void display();
        void updateWindow(GLFWwindow* window);
        void processMouseInput(GLFWwindow* window, double xPos, double yPos);
        void processMouseClick(GLFWwindow* window, int button, int action, int mods);
        void processKeyInput(GLFWwindow* window, int key, int scancode, int action, int mod);

    private:
        glm::mat4 projection_matrix;
        std::map<int, std::shared_ptr<Scene>> scene_map;
        std::shared_ptr<Scene> current_scene;
        bool should_close_window;

        std::shared_ptr<common::twod::RendererManager> renderer_manager;
    };
} // namespace common

#endif // SCENE_MANAGER_H