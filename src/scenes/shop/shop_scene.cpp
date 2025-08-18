#include "shop_scene.h"

#include <random>

#include "common/ecs/entity.h"
#include "common/resources/resource_manager.h"
#include "common/utils/bounding_box_2d.h"
#include "core/card_loader_xml.h"
#include "core/components/card_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"
#include "core/consts.h"
#include "core/renderutils/card_render_util.h"

namespace scenes {
namespace shop {

using common::ecs::Entity;
using core::components::CardComponent;
using core::components::PositionComponent;
using core::components::SizeComponent;

void ShopScene::render(
    std::shared_ptr<common::twod::RendererManager> renderer_manager) {
  // Render the background.
  auto sprite_renderer = renderer_manager->getSpriteRenderer();
  common::resources::Texture& white_texture =
      common::resources::ResourceManager::GetTexture("white_texture");
  sprite_renderer->DrawSprite(white_texture, glm::vec2(0.0f, 0.0f),
                              glm::vec2(core::SCREEN_WIDTH, core::SCREEN_HEIGHT),
                              0.0f, glm::vec4(0.4f, 0.3f, 0.2f, 1.0f));

  // Render the cards.
  for (auto& card_entity : cards_in_shop_) {
    card_render_util_->renderCard(card_entity, renderer_manager);
    CardComponent& card_component = *card_entity.getComponent<CardComponent>();
    PositionComponent& position_component =
        *card_entity.getComponent<PositionComponent>();
    SizeComponent& size_component = *card_entity.getComponent<SizeComponent>();

    glm::vec2 cost_position = position_component.getPosition();
    cost_position.y -= 30.0f;
    renderer_manager->getTextRenderer()->RenderText(
        std::to_string(card_component.getCost()), cost_position, 20.0f,
        core::COLOR_BLACK);
  }

  leave_button_->render(renderer_manager);
}

void ShopScene::processMouseInput(GLFWwindow* window, double x_pos,
                                  double y_pos) {
  mouse_position_ = convertMousePositionIntoScreenCoordinates(
      x_pos, y_pos, core::SCREEN_WIDTH, core::SCREEN_HEIGHT);
}

void ShopScene::processMouseClick(GLFWwindow* window, int button, int action,
                                  int mods) {
  if (wasLeftButtonClicked(button, action)) {
    if (leave_button_->containsPoint(mouse_position_)) {
      update_status_ = UpdateStatus::kSwitchScene;
      next_scene_id_ = static_cast<int>(core::SceneId::Map);
      return;
    }

    for (auto it = cards_in_shop_.begin(); it != cards_in_shop_.end(); ++it) {
      auto& card_entity = *it;
      PositionComponent& position_component =
          *card_entity.getComponent<PositionComponent>();
      SizeComponent& size_component = *card_entity.getComponent<SizeComponent>();
      common::utils::BoundingBox2D box{position_component.getPosition(),
                                       size_component.getSizeVec()};
      if (box.bottom_left.x <= mouse_position_.x &&
          box.bottom_left.x + box.size.x >= mouse_position_.x &&
          box.bottom_left.y <= mouse_position_.y &&
          box.bottom_left.y + box.size.y >= mouse_position_.y) {
        CardComponent& card_component =
            *card_entity.getComponent<CardComponent>();
        if (player_state_->getMoney() >= card_component.getCost()) {
          player_state_->setMoney(player_state_->getMoney() -
                                  card_component.getCost());
          player_state_->addCardToDeck(card_component.getId());
          cards_in_shop_.erase(it);
          break;
        }
      }
    }
  }
}

void ShopScene::loadScene() {
  card_render_util_ = std::make_unique<core::renderutils::CardRenderUtil>();
  core::CardLoaderXML card_loader;
  card_loader.loadCards("assets/cards/card_registry.xml", card_registry_);

  const auto& card_prototypes = card_registry_.getCardPrototypes();
  std::vector<int> card_ids;
  for (auto const& [id, components] : card_prototypes) {
    card_ids.push_back(id);
  }

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(card_ids.begin(), card_ids.end(), g);

  cards_in_shop_.clear();
  for (int i = 0; i < 10 && i < card_ids.size(); ++i) {
    Entity card_entity;
    auto components = card_registry_.getCardPrototype(card_ids[i]);
    for (auto& component : components) {
      card_entity.addComponent(component);
    }
    card_entity.getComponent<CardComponent>()->setIsFaceup(true);
    cards_in_shop_.push_back(std::move(card_entity));
  }

  // Position the cards.
  const float card_width = core::CARD_DEFAULT_WIDTH;
  const float card_height = core::CARD_DEFAULT_HEIGHT;
  const float x_padding = 50.0f;
  const float y_padding = 50.0f;
  const float x_start =
      (core::SCREEN_WIDTH - (5 * card_width + 4 * x_padding)) / 2.0f;
  const float y_start =
      (core::SCREEN_HEIGHT - (2 * card_height + y_padding)) / 2.0f;

  for (int i = 0; i < cards_in_shop_.size(); ++i) {
    int row = i / 5;
    int col = i % 5;
    float x_pos = x_start + col * (card_width + x_padding);
    float y_pos = y_start + row * (card_height + y_padding);
    cards_in_shop_[i]
        .getComponent<PositionComponent>()
        ->setPosition(glm::vec2(x_pos, y_pos));
  }

  common::resources::Texture& leave_button_texture =
      common::resources::ResourceManager::LoadTexture(
          "assets/mainmenu/exit_game_button.png", "leave_button",
          /*alpha=*/true);
  leave_button_ = std::make_shared<common::twod::Sprite>(
      leave_button_texture,
      glm::vec2(core::SCREEN_WIDTH - leave_button_texture.getWidth() - 20.0f,
                20.0f),
      leave_button_texture.getSizeVector());
}

}  // namespace shop
}  // namespace scenes
