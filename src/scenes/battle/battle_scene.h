#ifndef BATTLE_SCENE_H
#define BATTLE_SCENE_H

#include "common/scene.h"
#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "core/consts.h"

namespace scenes {
    namespace battle {

        class BattleScene : public common::Scene {
        public:
            BattleScene() : Scene(core::BATTLE_SCENE_ID), update_status(UpdateStatus::OK) {}

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
            UpdateStatus update_status;
            common::ecs::Engine ecs_engine;
        };
    } // namespace battle
} // namespace scenes

#endif // BATTLE_SCENE_H