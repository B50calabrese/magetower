#ifndef RENDERER_MANAGER_H
#define RENDERER_MANAGER_H

#include <memory>

#include "sprite_renderer.h"
#include "text_renderer.h"

namespace common {
    namespace twod {

        /*
        * Manages the various types of renderers used throughout a game (i.e. for sprits, text, etc.).
        */
        class RendererManager {
        public:
            RendererManager(glm::mat4 projection_matrix);

            std::shared_ptr<SpriteRenderer> getSpriteRenderer() {
                return this->sprite_renderer;
            }

            std::shared_ptr<TextRenderer> getTextRenderer() {
                return this->text_renderer;
            }

        private:
            std::shared_ptr<SpriteRenderer> sprite_renderer;
            std::shared_ptr<TextRenderer> text_renderer;
        };
    } // namespace twod
} // namespace common

#endif // RENDERER_MANAGER_H