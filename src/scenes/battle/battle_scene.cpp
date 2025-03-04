#include "battle_scene.h"

#include <iostream>

namespace scenes {
    namespace battle {

        void BattleScene::render(std::shared_ptr<common::twod::RendererManager> renderer_manager) {
            this->ecs_engine.runRenderSystems(renderer_manager);
        }

        void BattleScene::processMouseClick(GLFWwindow* window, int button, int action, int mods) {}

        void BattleScene::loadScene() {}

    } // namespace battle
} // namespace scenes