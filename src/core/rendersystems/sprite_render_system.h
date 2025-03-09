#ifndef SPRITE_RENDER_SYSTEM_H
#define SPRITE_RENDER_SYSTEM_H

#include <memory>

#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "common/ecs/render_system.h"

namespace core {
    namespace rendersystems {

        /*
        * This system is responsible for rendering entities denoted as sprites.
        * Entities that have the following components will be rendered:
        *   * PositionComponent
        *   * SizeComponent
        *   * TextureComponent
        *   * SpriteTagComponent
        */
        class SpriteRenderSystem : public common::ecs::RenderSystem {
        public:
            SpriteRenderSystem();

            void render(
                common::ecs::Engine& engine,
                std::shared_ptr<common::twod::RendererManager> renderer_manager);
        };

    } // namespace rendersystems
} // namespace core

#endif // SPRITE_RENDER_SYSTEM_H