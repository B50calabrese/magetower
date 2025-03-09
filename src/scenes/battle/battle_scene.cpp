#include "battle_scene.h"

#include "common/ecs/entity.h"
#include "core/components/card_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"
#include "core/components/sprite_tag_component.h"
#include "core/components/texture_component.h"
#include "core/events/mouse_click_event.h"
#include "core/rendersystems/card_render_system.h"
#include "core/rendersystems/sprite_render_system.h"

namespace scenes {
    namespace battle {

        using common::ecs::Entity;
        using core::components::CardComponent;
        using core::components::PositionComponent;
        using core::components::SizeComponent;
        using core::components::SpriteTagComponent;
        using core::components::TextureComponent;
        using core::events::MouseClickEvent;
        using core::rendersystems::CardRenderSystem;
        using core::rendersystems::SpriteRenderSystem;

        void BattleScene::render(std::shared_ptr<common::twod::RendererManager> renderer_manager) {
            this->ecs_engine.runRenderSystems(renderer_manager);
        }

        void BattleScene::processMouseClick(GLFWwindow* window, int button, int action, int mods) {
            this->ecs_engine.publishEvent(std::make_unique<MouseClickEvent>());
        }

        void BattleScene::loadScene() {
            this->loadEntities();
            this->loadSystems();
        }

        // Private functions

        void BattleScene::loadEntities() {
            // Generate an entity to represent the background on the screen.
            Entity& background_entity = this->ecs_engine.newEntity();
            background_entity.addComponent<TextureComponent>("battle_background", "assets/battle/background.png", /*alpha=*/ true);
            background_entity.addComponent<SizeComponent>(core::SCREEN_WIDTH, core::SCREEN_HEIGHT);
            background_entity.addComponent<PositionComponent>(glm::vec2(0.0f));
            background_entity.addComponent<SpriteTagComponent>();

            // Generate an entity to represent a test card;
            Entity& test_card = this->ecs_engine.newEntity();
            test_card.addComponent<SizeComponent>(120, 180);
            test_card.addComponent<PositionComponent>(glm::vec2(50.0f));
            test_card.addComponent<CardComponent>("Test name");
        }

        void BattleScene::loadSystems() {
            this->ecs_engine.registerRenderSystem<SpriteRenderSystem>();
            this->ecs_engine.registerRenderSystem<CardRenderSystem>();
        }

    } // namespace battle
} // namespace scenes