#include "scene_manager.h"

namespace common {

    void SceneManager::update(float deltaTimeMs) {
        if (this->current_scene != nullptr)
        this->current_scene->update(deltaTimeMs);
    }

    void SceneManager::display() {
        this->current_scene->render(this->renderer_manager);
    }

    void SceneManager::processInput(GLFWwindow* window) {}

    void SceneManager::processMouseInput(GLFWwindow* window, double xPos, double yPos) {}

    void SceneManager::processMouseClick(GLFWwindow* window, int button, int action, int mods) {}
} // namespace common