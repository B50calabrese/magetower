#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <map>
#include <memory>

#include "scene.h"

namespace common {
    
    /**
    * Handles the management of various scenes in a game.
    */
    class SceneManager {
    public:
        SceneManager() {}

        void addScene(std::shared_ptr<Scene> scene) {
            scene_map[scene->getId()] = scene;
        }

        void update();
        void display();
        void processInput(GLFWwindow* window);
        void processMouseInput(GLFWwindow* window, double xPos, double yPos);
        void processMouseClick(GLFWwindow* window, int button, int action, int mods);

    private:
        std::map<int, std::shared_ptr<Scene>> scene_map;
    };
} // namespace common

#endif // SCENE_MANAGER_H