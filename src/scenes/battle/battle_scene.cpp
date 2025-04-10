#include "battle_scene.h"

#include "common/ecs/entity.h"
#include "common/resources/resource_manager.h"
#include "core/components/animation_state_component.h"
#include "core/components/card_component.h"
#include "core/components/mouse_position_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"
#include "core/components/sprite_tag_component.h"
#include "core/components/texture_component.h"
#include "core/events/mouse_click_event.h"
#include "core/rendersystems/sprite_render_system.h"
#include "core/renderutils/card_render_util.h"
#include "core/systems/animation_system.h"
#include "scenes/battle/components/in_enemy_hand_tag_component.h"
#include "scenes/battle/components/in_player_hand_tag_component.h"
#include "scenes/battle/components/input_state_singleton_component.h"
#include "scenes/battle/components/enemy_deck_singleton_component.h"
#include "scenes/battle/components/player_deck_singleton_component.h"
#include "scenes/battle/events/player_draw_card_start_event.h"
#include "scenes/battle/events/player_hand_update_event.h"
#include "scenes/battle/rendersystems/card_render_system.h"
#include "scenes/battle/rendersystems/deck_render_system.h"
#include "scenes/battle/systems/card_hold_system.h"
#include "scenes/battle/systems/enemy_deck_system.h"
#include "scenes/battle/systems/enemy_hand_system.h"
#include "scenes/battle/systems/player_deck_system.h"
#include "scenes/battle/systems/player_hand_system.h"

namespace scenes {
    namespace battle {

        using common::ecs::Entity;
        using core::components::AnimationStateComponent;
        using core::components::CardComponent;
        using core::components::MousePositionComponent;
        using core::components::PositionComponent;
        using core::components::SizeComponent;
        using core::components::SpriteTagComponent;
        using core::components::TextureComponent;
        using core::events::MouseClickEvent;
        using core::rendersystems::SpriteRenderSystem;
        using core::renderutils::CardRenderUtil;
        using core::systems::AnimationSystem;
        using scenes::battle::components::InEnemyHandTagComponent;
        using scenes::battle::components::InPlayerHandTagComponent;
        using scenes::battle::components::InputStateSingletonComponent;
        using scenes::battle::components::EnemyDeckSingletonComponent;
        using scenes::battle::components::PlayerDeckSingletonComponent;
        using scenes::battle::events::PlayerDrawCardStartEvent;
        using scenes::battle::events::PlayerHandUpdateEvent;
        using scenes::battle::rendersystems::CardRenderSystem;
        using scenes::battle::rendersystems::DeckRenderSystem;
        using scenes::battle::systems::CardHoldSystem;
        using scenes::battle::systems::EnemyDeckSystem;
        using scenes::battle::systems::EnemyHandSystem;
        using scenes::battle::systems::PlayerDeckSystem;
        using scenes::battle::systems::PlayerHandSystem;

        void BattleScene::render(std::shared_ptr<common::twod::RendererManager> renderer_manager) {
            this->ecs_engine.runRenderSystems(renderer_manager);
        }

        void BattleScene::processMouseClick(GLFWwindow* window, int button, int action, int mods) {
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
                this->ecs_engine.publishEvent(std::make_unique<MouseClickEvent>());
        }

        void BattleScene::processKeyInput(GLFWwindow* window, int key, int scancode, int action, int mod) {
            if (key == GLFW_KEY_E && action == GLFW_PRESS) {
                this->ecs_engine.publishEvent(std::make_unique<PlayerDrawCardStartEvent>());
            }
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
            test_card.addComponent<CardComponent>(
                common::resources::ResourceManager::LoadTextureRelative(
                    "assets/cards/art/011_aqua_elemental.png", "011_aqua_elemental", /*alpha=*/ true),
                "Test name");
            test_card.getComponent<CardComponent>()->setIsFaceup(true);
            test_card.addComponent<InPlayerHandTagComponent>();

            Entity& test_card_2 = this->ecs_engine.newEntity();
            test_card_2.addComponent<SizeComponent>(120, 180);
            test_card_2.addComponent<PositionComponent>(glm::vec2(50.0f));
            test_card_2.addComponent<CardComponent>(
                common::resources::ResourceManager::LoadTextureRelative(
                    "assets/cards/art/012_merfolk_fledgling.png", "012_merfolk_fledgling", /*alpha=*/ true), 
                "Test name 2");
            test_card_2.getComponent<CardComponent>()->setIsFaceup(true);
            test_card_2.addComponent<InPlayerHandTagComponent>();

            Entity& test_card_3 = this->ecs_engine.newEntity();
            test_card_3.addComponent<SizeComponent>(120, 180);
            test_card_3.addComponent<PositionComponent>(glm::vec2(50.0f));
            test_card_3.addComponent<CardComponent>(
                common::resources::ResourceManager::LoadTextureRelative(
                    "assets/cards/art/013_blue_mage_apprentice.png", "013_blue_mage_apprentice", /*alpha=*/ true), 
                "Test name 3");
            test_card_3.getComponent<CardComponent>()->setIsFaceup(true);
            test_card_3.addComponent<InPlayerHandTagComponent>();

            Entity& test_card_4 = this->ecs_engine.newEntity();
            test_card_4.addComponent<SizeComponent>(120, 180);
            test_card_4.addComponent<PositionComponent>(glm::vec2(50.0f));
            test_card_4.addComponent<CardComponent>("Test name 4");
            test_card_4.addComponent<InEnemyHandTagComponent>();

            Entity& test_card_5 = this->ecs_engine.newEntity();
            test_card_5.addComponent<SizeComponent>(120, 180);
            test_card_5.addComponent<PositionComponent>(glm::vec2(50.0f));
            test_card_5.addComponent<CardComponent>("Test name");
            test_card_5.addComponent<InEnemyHandTagComponent>();

            Entity& test_card_6 = this->ecs_engine.newEntity();
            test_card_6.addComponent<SizeComponent>(120, 180);
            test_card_6.addComponent<PositionComponent>(glm::vec2(50.0f));
            test_card_6.addComponent<CardComponent>("Test name 2");
            test_card_6.addComponent<InEnemyHandTagComponent>();

            for (int i = 0; i < 10; i++) {
                Entity& player_deck_card = this->ecs_engine.newEntity();
                player_deck_card.addComponent<SizeComponent>(120, 180);
                player_deck_card.addComponent<PositionComponent>(glm::vec2(50.0f));
                player_deck_card.addComponent<CardComponent>("Test name 2");
                player_deck_card.getComponent<CardComponent>()->setIsVisible(false);
                ecs_engine.getSingletonComponent<PlayerDeckSingletonComponent>()->addCard(player_deck_card.getId());
            }

            Entity& test_card_8 = this->ecs_engine.newEntity();
            test_card_8.addComponent<SizeComponent>(120, 180);
            test_card_8.addComponent<PositionComponent>(glm::vec2(50.0f));
            test_card_8.addComponent<CardComponent>("Test name 8");
            test_card_8.getComponent<CardComponent>()->setIsVisible(false);

            ecs_engine.getSingletonComponent<EnemyDeckSingletonComponent>()->addCard(test_card_8.getId());

            ecs_engine.publishEvent(std::make_unique<PlayerHandUpdateEvent>());
        }

        void BattleScene::loadSystems() {
            this->ecs_engine.registerSystem<AnimationSystem>();

            std::shared_ptr<CardRenderUtil> card_render_util = std::make_shared<CardRenderUtil>();
            this->ecs_engine.registerRenderSystem<SpriteRenderSystem>();
            this->ecs_engine.registerRenderSystem<CardRenderSystem>(card_render_util);
            this->ecs_engine.registerRenderSystem<DeckRenderSystem>(card_render_util);

            this->ecs_engine.registerSystem<EnemyDeckSystem>();
            this->ecs_engine.registerSystem<PlayerDeckSystem>();
            this->ecs_engine.registerSystem<EnemyHandSystem>();
            this->ecs_engine.registerSystem<PlayerHandSystem>();
            this->ecs_engine.registerSystem<CardHoldSystem>();
        }

        void BattleScene::loadSingletonComponents() {
            this->ecs_engine.registerSingletonComponent<MousePositionComponent>(0.0f, 0.0f);
            this->ecs_engine.registerSingletonComponent<InputStateSingletonComponent>();
            this->ecs_engine.registerSingletonComponent<PlayerDeckSingletonComponent>();
            this->ecs_engine.registerSingletonComponent<EnemyDeckSingletonComponent>();
            this->ecs_engine.registerSingletonComponent<AnimationStateComponent>();
        }

    } // namespace battle
} // namespace scenes