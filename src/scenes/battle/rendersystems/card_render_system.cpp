#include "card_render_system.h"

#include "common/2D/renderer_manager.h"
#include "common/ecs/engine.h"
#include "common/ecs/entity.h"
#include "core/components/card_component.h"
#include "core/components/is_hovered_tag_component.h"
#include "core/renderutils/card_render_util.h"

namespace scenes {
    namespace battle {
        namespace rendersystems {

            using common::ecs::Engine;
            using common::ecs::Entity;
            using common::twod::RendererManager;
            using core::components::CardComponent;
            using core::components::IsHoveredTagComponent;
            using core::renderutils::CardRenderUtil;

            CardRenderSystem::CardRenderSystem(std::shared_ptr<CardRenderUtil> card_render_util) :
                card_render_util(card_render_util) {
                this->setRequiredComponent<CardComponent>();
            }

            void CardRenderSystem::render(Engine& engine, std::shared_ptr<RendererManager> renderer_manager) {
                std::shared_ptr<Entity> highlighted_entity;
                for (auto& entity : engine.getEntities()) {
                    if ((entity->getSignature() & this->getRequiredSignature()) == this->getRequiredSignature()) {
                        if (!entity->hasComponent<IsHoveredTagComponent>()) {
                            this->card_render_util->renderCard(*entity, renderer_manager);
                        }
                        else {
                            highlighted_entity = entity;
                        }
                    }
                }

                if (highlighted_entity != nullptr) {
                    this->card_render_util->renderCard(*highlighted_entity, renderer_manager);
                }
            }
        } // namespace rendersystems
    } // namespace battle
} // namespace scenes