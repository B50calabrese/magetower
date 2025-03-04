#ifndef BACKGROUND_SYSTEM_H
#define BACKGROUND_SYSTEM_H

#include <memory>

#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "common/ecs/render_system.h"

namespace scenes {
    namespace battle {
        namespace rendersystems {

            class BackgroundSystem : public common::ecs::RenderSystem {
            public:
                void render(
                    common::ecs::Engine& engine,
                    std::shared_ptr<common::twod::RendererManager> renderer_manager) {
                }
            };

        } // namespace rendersystems
    } // namespace battle
} // namespace scenes

#endif // BACKGROUND_SYSTEM_H