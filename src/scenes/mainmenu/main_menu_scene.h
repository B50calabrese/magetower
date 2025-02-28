#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include "common/scene.h"
#include "common/2D/renderer_manager.h"
#include "common/2D/sprite.h"
#include "common/resources/texture.h"
#include "core/consts.h"

namespace scenes {
    namespace mainmenu {

        class MainMenuScene : public common::Scene {
        public:
            const static int MAIN_MENU_SCENE_ID = 1;
            
            MainMenuScene() : Scene(MAIN_MENU_SCENE_ID), update_status(UpdateStatus::OK) {}

            void render(std::shared_ptr<common::twod::RendererManager> renderer_manager);

            UpdateStatus update(float delta_time_ms) {
                return this->update_status;
            }

            void processMouseInput(GLFWwindow* window, double xPos, double yPos) {
                this->mouse_position = this->convertMousePositionIntoScreenCoordinates(xPos, yPos, core::SCREEN_WIDTH, core::SCREEN_HEIGHT);
            }

            void processMouseClick(GLFWwindow* window, int button, int action, int mods);

            void loadScene();

            void unloadScene() {}

        private:
            common::resources::Texture background_texture;

            std::shared_ptr<common::twod::Sprite> start_button;
            std::shared_ptr<common::twod::Sprite> exit_button;

            UpdateStatus update_status;
        };
    }
} // namespace scenes

#endif // MAIN_MENU_SCENE_H