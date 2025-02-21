#include "sprite.h"

namespace common {
    namespace twod {

        void Sprite::render(std::shared_ptr<RendererManager> renderer_manager) {
            renderer_manager->getSpriteRenderer()->DrawSprite(
                this->getTexture(),
                this->getPosition(),
                this->getSize()
            );
        }

    } // namespace twod
} // namespace common