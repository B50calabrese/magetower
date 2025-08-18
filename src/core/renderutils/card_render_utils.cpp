#include "card_render_util.h"

#include "common/resources/resource_manager.h"
#include "common/resources/texture.h"
#include "core/components/card_component.h"
#include "core/components/is_hovered_tag_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"
#include "core/consts.h"

namespace core {
namespace renderutils {

namespace {
// Note these are represented as 'percentages' from the origin of the image (so
// that size of the image doesn't matter).
const glm::vec2 kArtPositionFactor = glm::vec2(
    16.0f / core::CARD_DEFAULT_WIDTH, 124.0f / core::CARD_DEFAULT_HEIGHT);
const glm::vec2 kArtSizeFactor = glm::vec2(
    166.0f / core::CARD_DEFAULT_WIDTH, 85.0f / core::CARD_DEFAULT_HEIGHT);

const glm::vec2 kNamePositionFactor = glm::vec2(
    16.0f / core::CARD_DEFAULT_WIDTH, 221.0f / core::CARD_DEFAULT_HEIGHT);
const glm::vec2 kNameSizeFactor = glm::vec2(
    166.0f / core::CARD_DEFAULT_WIDTH, 19.0f / core::CARD_DEFAULT_HEIGHT);
}  // namespace

CardRenderUtil::CardRenderUtil() {
  card_back_texture_ = &common::resources::ResourceManager::LoadTexture(
      "assets/cards/card_back.png", "card_back_texture", /*alpha=*/true);
  creature_card_frame_texture_ =
      &common::resources::ResourceManager::LoadTexture(
          "assets/cards/creature_frame.png", "creature_frame_texture",
          /*alpha=*/true);
  spell_card_frame_texture_ = &common::resources::ResourceManager::LoadTexture(
      "assets/cards/non_creature_frame.png", "non_creature_frame_texture",
      /*alpha=*/true);
}

void CardRenderUtil::renderCard(
    const common::ecs::Entity& entity,
    std::shared_ptr<common::twod::RendererManager> renderer_manager) {
  // If the entity isn't a card then return early.
  if (!entity.hasComponent<components::CardComponent>()) {
    return;
  }

  components::CardComponent& card =
      *entity.getComponent<components::CardComponent>();
  if (!card.isVisible()) {
    return;
  }

  // Get the card, position, and size components.
  components::PositionComponent& position =
      *entity.getComponent<components::PositionComponent>();
  components::SizeComponent& size =
      *entity.getComponent<components::SizeComponent>();
  glm::vec2 resolved_position = position.getPosition();

  common::resources::Texture& texture = card.isFaceup()
                                            ? *creature_card_frame_texture_
                                            : *card_back_texture_;
  renderer_manager->getSpriteRenderer()->DrawSprite(
      texture, resolved_position, size.getSizeVec(), 0.0f, glm::vec4(1.0f));

  if (card.isFaceup()) {
    renderer_manager->getSpriteRenderer()->DrawSprite(
        card.getCardArtTexture(),
        resolved_position + (size.getSizeVec() * kArtPositionFactor),
        size.getSizeVec() * kArtSizeFactor, 0.0f, glm::vec4(1.0f));
    renderer_manager->getTextRenderer()->RenderTextInBoundingBox(
        card.getName(),
        {resolved_position + (size.getSizeVec() * kNamePositionFactor),
         size.getSizeVec() * kNameSizeFactor},
        /*scale=*/16.0f, core::COLOR_BLACK,
        /*scale_to_fit=*/true);
  }
}

void CardRenderUtil::renderCardBack(
    glm::vec2 position, glm::vec2 size,
    std::shared_ptr<common::twod::RendererManager> renderer_manager) {
  renderer_manager->getSpriteRenderer()->DrawSprite(
      *card_back_texture_, position, size, 0.0f, glm::vec4(1.0f));
}

}  // namespace renderutils
}  // namespace core