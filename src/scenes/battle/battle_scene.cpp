#include "battle_scene.h"

#include "common/ecs/entity.h"
#include "core/components/card_component.h"
#include "core/components/mouse_position_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"
#include "core/components/sprite_tag_component.h"
#include "core/components/texture_component.h"
#include "core/events/mouse_click_event.h"
#include "core/rendersystems/sprite_render_system.h"
#include "core/renderutils/card_render_util.h"
#include "scenes/battle/components/in_player_hand_tag_component.h"
#include "scenes/battle/components/input_state_singleton_component.h"
#include "scenes/battle/events/player_hand_update_event.h"
#include "scenes/battle/rendersystems/card_render_system.h"
#include "scenes/battle/systems/card_hold_system.h"
#include "scenes/battle/systems/player_hand_system.h"

namespace scenes {
    namespace battle {

        using common::ecs::Entity;
        using core::components::CardComponent;
        using core::components::MousePositionComponent;
        using core::components::PositionComponent;
        using core::components::SizeComponent;
        using core::components::SpriteTagComponent;
        using core::components::TextureComponent;
        using core::events::MouseClickEvent;
        using core::rendersystems::SpriteRenderSystem;
        using core::renderutils::CardRenderUtil;
        using scenes::battle::components::InPlayerHandTagComponent;
        using scenes::battle::components::InputStateSingletonComponent;
        using scenes::battle::events::PlayerHandUpdateEvent;
        using scenes::battle::rendersystems::CardRenderSystem;
        using scenes::battle::systems::CardHoldSystem;
        using scenes::battle::systems::PlayerHandSystem;

        void BattleScene::render(std::shared_ptr<common::twod::RendererManager> renderer_manager) {
            this->ecs_engine.runRenderSystems(renderer_manager);
        }

        void BattleScene::processMouseClick(GLFWwindow* window, int button, int action, int mods) {
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
                this->ecs_engine.publishEvent(std::make_unique<MouseClickEvent>());
        }

        void BattleScene::loadScene() {
            this->loadSystems();
            this->loadSingletonComponents();
            this->loadEntities();
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
            test_card.addComponent<InPlayerHandTagComponent>();

            Entity& test_card_2 = this->ecs_engine.newEntity();
            test_card_2.addComponent<SizeComponent>(120, 180);
            test_card_2.addComponent<PositionComponent>(glm::vec2(50.0f));
            test_card_2.addComponent<CardComponent>("Test name 2");
            test_card_2.addComponent<InPlayerHandTagComponent>();

            ecs_engine.publishEvent(std::make_unique<PlayerHandUpdateEvent>());
        }

        void BattleScene::loadSystems() {
            std::shared_ptr<CardRenderUtil> card_render_util = std::make_shared<CardRenderUtil>();
            this->ecs_engine.registerRenderSystem<SpriteRenderSystem>();
            this->ecs_engine.registerRenderSystem<CardRenderSystem>(card_render_util);

            this->ecs_engine.registerSystem<PlayerHandSystem>();
            this->ecs_engine.registerSystem<CardHoldSystem>();
        }

        void BattleScene::loadSingletonComponents() {
            this->ecs_engine.registerSingletonComponent<MousePositionComponent>(0.0f, 0.0f);
            this->ecs_engine.registerSingletonComponent<InputStateSingletonComponent>();
        }

    } // namespace battle
} // namespace scenes