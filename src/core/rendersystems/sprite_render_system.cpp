#include "sprite_render_system.h"

#include "core/components/position_component.h"
#include "core/components/size_component.h"
#include "core/components/sprite_tag_component.h"
#include "core/components/texture_component.h"

namespace core {
    namespace rendersystems {

        using core::components::PositionComponent;
        using core::components::SizeComponent;
        using core::components::SpriteTagComponent;
        using core::components::TextureComponent;

        SpriteRenderSystem::SpriteRenderSystem() {
            this->setRequiredComponent<PositionComponent>();
            this->setRequiredComponent<SizeComponent>();
            this->setRequiredComponent<SpriteTagComponent>();
            this->setRequiredComponent<TextureComponent>();
        }

        void SpriteRenderSystem::render(
            common::ecs::Engine& engine,
            std::shared_ptr<common::twod::RendererManager> renderer_manager) {
            for (auto& entity : engine.getEntities()) {
                if ((entity->getSignature() & this->getRequiredSignature()) == this->getRequiredSignature()) {
                    renderer_manager->getSpriteRenderer()->DrawSprite(
                        entity->getComponent<TextureComponent>()->getTexture(),
                        entity->getComponent<PositionComponent>()->getPosition(),
                        glm::vec2(
                            entity->getComponent<SizeComponent>()->getWidth(),
                            entity->getComponent<SizeComponent>()->getHeight()
                        ));
                }
            }
        }

    } // namespace rendersystems
} // namespace core