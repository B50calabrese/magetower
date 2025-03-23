#ifndef CARD_RENDER_UTIL_H
#define CARD_RENDER_UTIL_H

#include <memory>

#include "common/2D/renderer_manager.h"
#include "common/resources/texture.h"
#include "common/ecs/engine.h"

namespace core {
    namespace renderutils {

        /*
        * Utility class for rendering cards/card backs. It encapsulates the positioning of card information, and avoids having
        * multiple references to the same set of card frames/backs.
        */
        class CardRenderUtil {
        public:
            CardRenderUtil();

            void renderCard(const common::ecs::Entity& entity, std::shared_ptr<common::twod::RendererManager> renderer_manager);

            void renderCardBack(glm::vec2 position, glm::vec2 size, std::shared_ptr<common::twod::RendererManager> renderer_manager);

        private:
            common::resources::Texture card_back_texture;
            common::resources::Texture creature_card_frame_texture;
            common::resources::Texture spell_card_frame_texture;
        };

    } // namespace renderutils
} // namespace core

#endif // CARD_RENDER_UTIL_H