#ifndef PLAYER_DECK_RENDER_SYSTEM_H
#define PLAYER_DECK_RENDER_SYSTEM_H

#include <memory>

#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "common/ecs/render_system.h"
#include "core/renderutils/card_render_util.h"

namespace scenes {
    namespace battle {
        namespace rendersystems {

            /*
            * This system is responsible for rendering the player's deck.
            */
            class PlayerDeckRenderSystem : public common::ecs::RenderSystem {
            public:
                PlayerDeckRenderSystem(std::shared_ptr<core::renderutils::CardRenderUtil> card_render_util);

                void render(
                    common::ecs::Engine& engine,
                    std::shared_ptr<common::twod::RendererManager> renderer_manager);

            private:
                const static glm::vec2 DECK_SIZE;

                std::shared_ptr<core::renderutils::CardRenderUtil> card_render_util;
            };

        } // namespace rendersystems
    } // namespace battle
} // namespace scenes

#endif // PLAYER_DECK_RENDER_SYSTEM_H