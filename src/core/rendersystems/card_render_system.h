#ifndef CARD_RENDER_SYSTEM_H
#define CARD_RENDER_SYSTEM_H

#include <memory>

#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "common/ecs/render_system.h"
#include "core/renderutils/card_render_util.h"

namespace core {
    namespace rendersystems {

        /*
        * This system is responsible for rendering entities marked as cards (presence of the CardComponent)
        */
        class CardRenderSystem : public common::ecs::RenderSystem {
        public:
            CardRenderSystem();

            void render(
                common::ecs::Engine& engine,
                std::shared_ptr<common::twod::RendererManager> renderer_manager);

        private:
            core::renderutils::CardRenderUtil card_render_util;
        };

    } // namespace rendersystems
} // namespace core

#endif // CARD_RENDER_SYSTEM_H