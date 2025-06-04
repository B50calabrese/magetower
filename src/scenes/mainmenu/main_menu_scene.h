#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include "common/scene.h"
#include "common/2D/renderer_manager.h"
#include "common/2D/sprite.h"
#include "common/resources/texture.h"
#include "core/consts.h"
#include "core/scene_ids.h"

namespace scenes {
    namespace mainmenu {

        class MainMenuScene : public common::Scene {
        public:          
            MainMenuScene() : Scene(static_cast<int>(core::SceneId::MainMenu)), update_status(UpdateStatus::OK) {}

            void render(std::shared_ptr<common::twod::RendererManager> renderer_manager);

            UpdateStatus update(double delta_time_ms) {
                return this->update_status;
            }

            void processMouseInput(GLFWwindow* window, double xPos, double yPos) {
                this->mouse_position = this->convertMousePositionIntoScreenCoordinates(xPos, yPos, core::SCREEN_WIDTH, core::SCREEN_HEIGHT);
            }

            void processMouseClick(GLFWwindow* window, int button, int action, int mods);

            void processKeyInput(GLFWwindow* window, int key, int scancode, int action, int mod) {}

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