#include "card_render_util.h"

#include "common/resources/resource_manager.h"
#include "common/resources/texture.h"
#include "core/consts.h"
#include "core/components/card_component.h"
#include "core/components/is_hovered_tag_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"

namespace core {
    namespace renderutils {

        using common::ecs::Entity;
        using common::twod::RendererManager;
        using common::resources::Texture;
        using core::components::CardComponent;
        using core::components::IsHoveredTagComponent;
        using core::components::PositionComponent;
        using core::components::SizeComponent;

        // Note these are represented as 'percentages' from the origin of the image (so that size of the image doesn't matter).
        const static glm::vec2 ART_POSITION_FACTOR = glm::vec2(16.0f / core::CARD_DEFAULT_WIDTH, 124.0f / core::CARD_DEFAULT_HEIGHT);
        const static glm::vec2 ART_SIZE_FACTOR = glm::vec2(166.0f / core::CARD_DEFAULT_WIDTH, 85.0f / core::CARD_DEFAULT_HEIGHT);
        
        const static glm::vec2 NAME_POSITION_FACTOR = glm::vec2(16.0f / core::CARD_DEFAULT_WIDTH, 221.0f / core::CARD_DEFAULT_HEIGHT);
        const static glm::vec2 NAME_SIZE_FACTOR = glm::vec2(166.0f / core::CARD_DEFAULT_WIDTH, 19.0f / core::CARD_DEFAULT_HEIGHT);

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

            CardComponent card = *entity.getComponent<CardComponent>();
            if (!card.isVisible()) {
                return;
            }

            // Get the card, position, and size components.
            PositionComponent position = *entity.getComponent<PositionComponent>();
            SizeComponent size = *entity.getComponent<SizeComponent>();
            glm::vec2 resolved_position = position.getPosition();

            Texture& texture = card.isFaceup() ? this->creature_card_frame_texture : this->card_back_texture;
            renderer_manager->getSpriteRenderer()->DrawSprite(
                texture,
                resolved_position,
                size.getSizeVec()
            );

            if (card.isFaceup()) {
                renderer_manager->getSpriteRenderer()->DrawSprite(
                    card.getCardArtTexture(),
                    resolved_position + (size.getSizeVec() * ART_POSITION_FACTOR),
                    size.getSizeVec() * ART_SIZE_FACTOR
                );
                renderer_manager->getTextRenderer()->RenderTextInBoundingBox(
                    card.getName(),
                    {
                        resolved_position + (size.getSizeVec() * NAME_POSITION_FACTOR),
                        size.getSizeVec() * NAME_SIZE_FACTOR
                    },
                    /*scale=*/ 16.0f,
                    core::COLOR_BLACK,
                    /*scale_to_fit=*/ true
                );
            }
        }

        void CardRenderUtil::renderCardBack(glm::vec2 position, glm::vec2 size, std::shared_ptr<common::twod::RendererManager> renderer_manager) {
            renderer_manager->getSpriteRenderer()->DrawSprite(
                this->card_back_texture,
                position,
                size
            );
        }

    } // namespace renderutils
} // namespace core