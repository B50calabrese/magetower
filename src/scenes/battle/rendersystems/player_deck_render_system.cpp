#include "player_deck_render_system.h"

#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "common/ecs/entity.h"
#include "core/renderutils/card_render_util.h"
#include "scenes/battle/components/player_deck_singleton_component.h"

namespace scenes {
    namespace battle {
        namespace rendersystems {

            using common::ecs::Engine;
            using common::ecs::Entity;
            using common::twod::RendererManager;
            using core::renderutils::CardRenderUtil;
            using scenes::battle::components::PlayerDeckSingletonComponent;

            const glm::vec2 PlayerDeckRenderSystem::DECK_POSITION = glm::vec2(1703, 35);
            const glm::vec2 PlayerDeckRenderSystem::DECK_SIZE = glm::vec2(183, 247);

            PlayerDeckRenderSystem::PlayerDeckRenderSystem(std::shared_ptr<CardRenderUtil> card_render_util) :
                card_render_util(card_render_util) {}

            void PlayerDeckRenderSystem::render(Engine& engine, std::shared_ptr<RendererManager> renderer_manager) {
                PlayerDeckSingletonComponent* deck = engine.getSingletonComponent<PlayerDeckSingletonComponent>();

                if (deck->getSizeOfDeck() > 0) {
                    this->card_render_util->renderCardBack(
                        PlayerDeckRenderSystem::DECK_POSITION,
                        PlayerDeckRenderSystem::DECK_SIZE,
                        renderer_manager
                    );
                }
            }
        } // namespace rendersystems
    } // namespace battle
} // namespace scenes