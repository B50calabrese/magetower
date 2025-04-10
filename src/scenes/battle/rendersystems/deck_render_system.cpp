#include "deck_render_system.h"

#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "common/ecs/entity.h"
#include "core/consts.h"
#include "core/renderutils/card_render_util.h"
#include "scenes/battle/components/enemy_deck_singleton_component.h"
#include "scenes/battle/components/player_deck_singleton_component.h"

namespace scenes {
    namespace battle {
        namespace rendersystems {

            using common::ecs::Engine;
            using common::ecs::Entity;
            using common::twod::RendererManager;
            using core::renderutils::CardRenderUtil;
            using scenes::battle::components::EnemyDeckSingletonComponent;
            using scenes::battle::components::PlayerDeckSingletonComponent;

            const glm::vec2 DeckRenderSystem::DECK_SIZE = glm::vec2(183, 247);

            DeckRenderSystem::DeckRenderSystem(std::shared_ptr<CardRenderUtil> card_render_util) :
                card_render_util(card_render_util) {}

            void DeckRenderSystem::render(Engine& engine, std::shared_ptr<RendererManager> renderer_manager) {
                PlayerDeckSingletonComponent* player_deck = engine.getSingletonComponent<PlayerDeckSingletonComponent>();

                if (player_deck->getSizeOfDeck() > 0) {
                    this->card_render_util->renderCardBack(
                        core::PLAYER_DECK_POSITION,
                        DeckRenderSystem::DECK_SIZE,
                        renderer_manager
                    );
                }

                EnemyDeckSingletonComponent* enemy_deck = engine.getSingletonComponent<EnemyDeckSingletonComponent>();

                if (enemy_deck->getSizeOfDeck() > 0) {
                    this->card_render_util->renderCardBack(
                        core::ENEMY_DECK_POSITION,
                        DeckRenderSystem::DECK_SIZE,
                        renderer_manager
                    );
                }
            }
        } // namespace rendersystems
    } // namespace battle
} // namespace scenes