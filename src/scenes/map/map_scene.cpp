#include "map_scene.h"

#include <random>

#include "common/resources/resource_manager.h"
#include "common/utils/bounding_box_2d.h"
#include "core/consts.h"

namespace scenes {
namespace map {

void MapScene::render(
    std::shared_ptr<common::twod::RendererManager> renderer_manager) {
  auto sprite_renderer = renderer_manager->getSpriteRenderer();

  // Render the background.
  common::resources::Texture& white_texture =
      common::resources::ResourceManager::GetTexture("white_texture");
  sprite_renderer->DrawSprite(white_texture, glm::vec2(0.0f, 0.0f),
                              glm::vec2(core::SCREEN_WIDTH, core::SCREEN_HEIGHT),
                              0.0f, glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

  // Render the connections.
  for (const auto& node : nodes_) {
    for (int child_index : node.children) {
      sprite_renderer->DrawLine(node.position, nodes_[child_index].position,
                                5.0f, glm::vec4(1.0f));
    }
  }

  // Render the nodes.
  for (const auto& node : nodes_) {
    common::resources::Texture* texture = nullptr;
    switch (node.type) {
      case NodeType::kBattle:
        texture = &common::resources::ResourceManager::GetTexture(
            "map_node_battle");
        break;
      case NodeType::kInteraction:
        texture = &common::resources::ResourceManager::GetTexture(
            "map_node_interaction");
        break;
      case NodeType::kShop:
        texture =
            &common::resources::ResourceManager::GetTexture("map_node_shop");
        break;
    }
    glm::vec4 color = (node.level == player_state_->getCurrentMapLevel())
                          ? glm::vec4(1.0f)
                          : glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    sprite_renderer->DrawSprite(*texture, node.position,
                                texture->getSizeVector(), 0.0f, color);
  }

  if (state_ == MapState::kInteraction) {
    renderInteractionOverlay(renderer_manager);
  }
}

void MapScene::processMouseInput(GLFWwindow* window, double x_pos,
                                 double y_pos) {
  mouse_position_ = convertMousePositionIntoScreenCoordinates(
      x_pos, y_pos, core::SCREEN_WIDTH, core::SCREEN_HEIGHT);
}

void MapScene::processMouseClick(GLFWwindow* window, int button, int action,
                                 int mods) {
  if (wasLeftButtonClicked(button, action)) {
    if (state_ == MapState::kMap) {
      for (const auto& node : nodes_) {
        if (node.level != player_state_->getCurrentMapLevel()) {
          continue;
        }
        common::resources::Texture* texture = nullptr;
        switch (node.type) {
          case NodeType::kBattle:
            texture = &common::resources::ResourceManager::GetTexture(
                "map_node_battle");
            break;
          case NodeType::kInteraction:
            texture = &common::resources::ResourceManager::GetTexture(
                "map_node_interaction");
            break;
          case NodeType::kShop:
            texture = &common::resources::ResourceManager::GetTexture(
                "map_node_shop");
            break;
        }
        common::utils::BoundingBox2D box{node.position,
                                         texture->getSizeVector()};
        if (box.bottom_left.x <= mouse_position_.x &&
            box.bottom_left.x + box.size.x >= mouse_position_.x &&
            box.bottom_left.y <= mouse_position_.y &&
            box.bottom_left.y + box.size.y >= mouse_position_.y) {
          switch (node.type) {
            case NodeType::kBattle:
              update_status_ = UpdateStatus::kSwitchScene;
              next_scene_id_ = static_cast<int>(core::SceneId::Battle);
              break;
            case NodeType::kInteraction:
              state_ = MapState::kInteraction;
              generateInteractionEvent();
              break;
            case NodeType::kShop:
              update_status_ = UpdateStatus::kSwitchScene;
              next_scene_id_ = static_cast<int>(core::SceneId::Shop);
              break;
          }
        }
      }
    } else if (state_ == MapState::kInteraction) {
      common::utils::BoundingBox2D option1_box{
          glm::vec2(core::HALF_SCREEN_WIDTH - 100.0f,
                    core::HALF_SCREEN_HEIGHT - 50.0f),
          glm::vec2(100.0f, 30.0f)};
      common::utils::BoundingBox2D option2_box{
          glm::vec2(core::HALF_SCREEN_WIDTH + 100.0f,
                    core::HALF_SCREEN_HEIGHT - 50.0f),
          glm::vec2(100.0f, 30.0f)};

      if (option1_box.bottom_left.x <= mouse_position_.x &&
          option1_box.bottom_left.x + option1_box.size.x >=
              mouse_position_.x &&
          option1_box.bottom_left.y <= mouse_position_.y &&
          option1_box.bottom_left.y + option1_box.size.y >=
              mouse_position_.y) {
        current_event_.option1_effect();
        player_state_->setCurrentMapLevel(player_state_->getCurrentMapLevel() +
                                          1);
        state_ = MapState::kMap;
      } else if (option2_box.bottom_left.x <= mouse_position_.x &&
                 option2_box.bottom_left.x + option2_box.size.x >=
                     mouse_position_.x &&
                 option2_box.bottom_left.y <= mouse_position_.y &&
                 option2_box.bottom_left.y + option2_box.size.y >=
                     mouse_position_.y) {
        current_event_.option2_effect();
        player_state_->setCurrentMapLevel(player_state_->getCurrentMapLevel() +
                                          1);
        state_ = MapState::kMap;
      }
    }
  }
}

void MapScene::generateInteractionEvent() {
  current_event_.text = "You found a potion! Do you drink it?";
  current_event_.option1_text = "Yes";
  current_event_.option2_text = "No";
  current_event_.option1_effect = [this]() {
    player_state_->setHealth(player_state_->getHealth() + 5);
    player_state_->setMoney(player_state_->getMoney() - 10);
  };
  current_event_.option2_effect = []() {};
}

void MapScene::renderInteractionOverlay(
    std::shared_ptr<common::twod::RendererManager> renderer_manager) {
  auto sprite_renderer = renderer_manager->getSpriteRenderer();
  common::resources::Texture& white_texture =
      common::resources::ResourceManager::GetTexture("white_texture");
  sprite_renderer->DrawSprite(
      white_texture, glm::vec2(0.0f, 0.0f),
      glm::vec2(core::SCREEN_WIDTH, core::SCREEN_HEIGHT), 0.0f,
      glm::vec4(0.0f, 0.0f, 0.0f, 0.5f));

  renderer_manager->getTextRenderer()->RenderText(
      current_event_.text,
      glm::vec2(core::HALF_SCREEN_WIDTH - 200.0f, core::HALF_SCREEN_HEIGHT),
      30.0f, glm::vec3(1.0f, 1.0f, 1.0f));

  renderer_manager->getTextRenderer()->RenderText(
      current_event_.option1_text,
      glm::vec2(core::HALF_SCREEN_WIDTH - 100.0f,
                core::HALF_SCREEN_HEIGHT - 50.0f),
      20.0f, glm::vec3(1.0f, 1.0f, 1.0f));

  renderer_manager->getTextRenderer()->RenderText(
      current_event_.option2_text,
      glm::vec2(core::HALF_SCREEN_WIDTH + 100.0f,
                core::HALF_SCREEN_HEIGHT - 50.0f),
      20.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void MapScene::loadScene() {
  common::resources::ResourceManager::LoadTexture(
      "assets/mainmenu/start_game_button.png", "map_node_battle",
      /*alpha=*/true);
  common::resources::ResourceManager::LoadTexture(
      "assets/mainmenu/test.png", "map_node_interaction",
      /*alpha=*/true);
  common::resources::ResourceManager::LoadTexture(
      "assets/mainmenu/exit_game_button.png", "map_node_shop",
      /*alpha=*/true);

  generateMap();
}

void MapScene::generateMap() {
  nodes_.clear();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> node_type_distrib(0, 2);
  std::uniform_int_distribution<> nodes_per_level_distrib(1, 3);
  std::uniform_int_distribution<> child_distrib(0, 2);

  const int num_levels = 5;
  const float level_height = core::SCREEN_HEIGHT / (num_levels + 1);
  int node_index = 0;
  int nodes_in_previous_level = 0;

  for (int i = 0; i < num_levels; ++i) {
    int nodes_in_level = nodes_per_level_distrib(gen);
    float node_width = core::SCREEN_WIDTH / (nodes_in_level + 1);
    int previous_level_start_index = node_index - nodes_in_previous_level;

    for (int j = 0; j < nodes_in_level; ++j) {
      MapNode node;
      node.type = static_cast<NodeType>(node_type_distrib(gen));
      node.position =
          glm::vec2(node_width * (j + 1), level_height * (i + 1));
      node.level = i;

      if (i > 0) {
        int parent_index =
            previous_level_start_index + (j % nodes_in_previous_level);
        nodes_[parent_index].children.push_back(node_index);
      }
      nodes_.push_back(node);
      node_index++;
    }
    nodes_in_previous_level = nodes_in_level;
  }
}

}  // namespace map
}  // namespace scenes
