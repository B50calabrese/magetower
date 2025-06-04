#ifndef BATTLE_SCENE_H
#define BATTLE_SCENE_H

#include "common/scene.h"
#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "core/consts.h"
#include "core/card_registry.h"
#include "core/components/mouse_position_component.h"

namespace scenes {
    namespace battle {

        class BattleScene : public common::Scene {
        public:
            BattleScene() : Scene(core::BATTLE_SCENE_ID), update_status(UpdateStatus::OK) {
                this->card_registry = std::make_shared<core::CardRegistry>();
            }

            void render(std::shared_ptr<common::twod::RendererManager> renderer_manager);

            UpdateStatus update(double delta_time_ms) {
                this->ecs_engine.runSystems(delta_time_ms);
                return this->update_status;
            }

            void processMouseInput(GLFWwindow* window, double xPos, double yPos) {
                auto mouse_component = this->ecs_engine.getSingletonComponent<core::components::MousePositionComponent>();
                glm::vec2 position = this->convertMousePositionIntoScreenCoordinates(xPos, yPos, core::SCREEN_WIDTH, core::SCREEN_HEIGHT);
                mouse_component->setX(position.x);
                mouse_component->setY(position.y);
            }

            void processMouseClick(GLFWwindow* window, int button, int action, int mods);

            void processKeyInput(GLFWwindow* window, int key, int scancode, int action, int mod);

            void loadScene();

            void unloadScene() {}

        private:
            void loadEntities();

            void loadPlayerDeck();

            void loadEnemyDeck();

            void loadSystems();

            void loadRenderSystems();

            void loadSingletonComponents();

            UpdateStatus update_status;
            common::ecs::Engine ecs_engine;

            std::shared_ptr<core::CardRegistry> card_registry;
        };
    } // namespace battle
} // namespace scenes

#endif // BATTLE_SCENE_H