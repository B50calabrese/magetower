#include "card_render_util.h"

#include "common/resources/resource_manager.h"
#include "core/components/card_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"

namespace core {
    namespace renderutils {

        using common::ecs::Entity;
        using common::twod::RendererManager;
        using core::components::CardComponent;
        using core::components::PositionComponent;
        using core::components::SizeComponent;

        CardRenderUtil::CardRenderUtil() {
            this->card_back_texture = common::resources::ResourceManager::LoadTextureRelative(
                "assets/cards/card_back.png", "card_back_texture", /*alpha=*/ true
            );
            this->creature_card_frame_texture = common::resources::ResourceManager::LoadTextureRelative(
                "assets/cards/creature_frame.png", "creature_frame_texture", /*alpha=*/ true
            );
            this->spell_card_frame_texture = common::resources::ResourceManager::LoadTextureRelative(
                "assets/cards/non_creature_frame.png", "non_creature_frame_texture", /*alpha=*/ true
            );
        }

        void CardRenderUtil::renderCard(const Entity& entity, std::shared_ptr<RendererManager> renderer_manager) {
            // If the entity isn't a card then return early.
            if (!entity.hasComponent<CardComponent>()) {
                return;
            }

            // Get the position and size components.
            PositionComponent position = *entity.getComponent<PositionComponent>();
            SizeComponent size = *entity.getComponent<SizeComponent>();

            renderer_manager->getSpriteRenderer()->DrawSprite(
                this->card_back_texture,
                position.getPosition(),
                glm::vec2(size.getWidth(), size.getHeight())
            );
        }

    } // namespace renderutils
} // namespace core