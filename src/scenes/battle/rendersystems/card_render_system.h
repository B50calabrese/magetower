#ifndef CARD_RENDER_SYSTEM_H
#define CARD_RENDER_SYSTEM_H

#include <memory>

#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "common/ecs/render_system.h"
#include "core/renderutils/card_render_util.h"

namespace scenes {
    namespace battle {
        namespace rendersystems {

            /*
            * This system is responsible for rendering cards on the screen.
            */
            class CardRenderSystem : public common::ecs::RenderSystem {
            public:
                CardRenderSystem(std::shared_ptr<core::renderutils::CardRenderUtil> card_render_util);

                void render(
                    common::ecs::Engine& engine,
                    std::shared_ptr<common::twod::RendererManager> renderer_manager);

            private:
                std::shared_ptr<core::renderutils::CardRenderUtil> card_render_util;
            };

        } // namespace rendersystems
    } // namespace battle
} // namespace scenes

#endif // CARD_RENDER_SYSTEM_H