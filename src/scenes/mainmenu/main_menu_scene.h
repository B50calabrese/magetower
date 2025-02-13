#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include "common/scene.h"

namespace scenes {
    namespace mainmenu {

        class MainMenuScene : public common::Scene {
        public:
            const static int MAIN_MENU_SCENE_ID = 1;
            
            MainMenuScene() : Scene(MAIN_MENU_SCENE_ID) {}

            void render() {}

            UpdateStatus update(float deltaTime) {
                return UpdateStatus::OK;
            }

            void processInput(GLFWwindow* window) {

            }

            void processMouseInput(GLFWwindow* window, double xPos, double yPos) {

            }

            void processMouseClick(GLFWwindow* window, int button, int action, int mods) {

            }

            void loadScene() {}
        };
    }
} // namespace scenes

#endif // MAIN_MENU_SCENE_H