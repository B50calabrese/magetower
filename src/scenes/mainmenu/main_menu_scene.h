#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include "common/scene.h"
#include "common/2D/renderer_manager.h"
#include "common/resources/texture.h"

namespace scenes {
    namespace mainmenu {

        class MainMenuScene : public common::Scene {
        public:
            const static int MAIN_MENU_SCENE_ID = 1;
            
            MainMenuScene() : Scene(MAIN_MENU_SCENE_ID) {}

            void render(std::shared_ptr<common::twod::RendererManager> renderer_manager);

            UpdateStatus update(float delta_time_ms) {
                return UpdateStatus::OK;
            }

            void processInput(GLFWwindow* window) {

            }

            void processMouseInput(GLFWwindow* window, double xPos, double yPos) {

            }

            void processMouseClick(GLFWwindow* window, int button, int action, int mods) {

            }

            void loadScene();

            void unloadScene() {}

        private:
            common::resources::Texture background_texture;
        };
    }
} // namespace scenes

#endif // MAIN_MENU_SCENE_H