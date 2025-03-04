#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <memory>

#include "common/2D/renderer_manager.h"

namespace common {
    namespace ecs {

        class Engine;

        /* Base class for systems that render based on components. */
        class RenderSystem {
        public:
            virtual ~RenderSystem() = default;

            // This is the main function that render systems need to override to draw.
            virtual void render(Engine& engine, std::shared_ptr<common::twod::RendererManager> renderer_manager) = 0;
        };

    } // namespace ecs
} // namespace common

#endif // RENDER_SYSTEM_H