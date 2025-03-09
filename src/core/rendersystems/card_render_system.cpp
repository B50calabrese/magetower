#include "card_render_system.h"

#include "core/components/card_component.h"

namespace core {
    namespace rendersystems {

        using core::components::CardComponent;

        CardRenderSystem::CardRenderSystem() {
            this->setRequiredComponent<CardComponent>();
        }

        void CardRenderSystem::render(
            common::ecs::Engine& engine,
            std::shared_ptr<common::twod::RendererManager> renderer_manager) {
            for (auto& entity : engine.getEntities()) {
                if ((entity->getSignature() & this->getRequiredSignature()) == this->getRequiredSignature()) {
                    this->card_render_util.renderCard(*entity, renderer_manager);
                }
            }
        }

    } // namespace rendersystems
} // namespace core