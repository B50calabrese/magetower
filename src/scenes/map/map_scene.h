#ifndef SCENES_MAP_MAP_SCENE_H_
#define SCENES_MAP_MAP_SCENE_H_

#include <string>
#include <vector>

#include "common/scene.h"
#include "core/scene_ids.h"

namespace scenes {
namespace map {

enum class NodeType { kBattle, kInteraction, kShop };

struct MapNode {
  NodeType type;
  glm::vec2 position;
  std::vector<int> children;
};

enum class MapState { kMap, kInteraction };

struct InteractionEvent {
  std::string text;
  std::string option1_text;
  std::string option2_text;
  std::function<void()> option1_effect;
  std::function<void()> option2_effect;
};

class MapScene : public common::Scene {
 public:
  MapScene()
      : common::Scene(static_cast<int>(core::SceneId::Map)),
        update_status_(UpdateStatus::kOk),
        state_(MapState::kMap) {}

  void render(
      std::shared_ptr<common::twod::RendererManager> renderer_manager) override;
  void processMouseInput(GLFWwindow* window, double x_pos,
                         double y_pos) override;
  void processMouseClick(GLFWwindow* window, int button, int action,
                         int mods) override;
  void processKeyInput(GLFWwindow* window, int key, int scancode, int action,
                       int mod) override {}
  UpdateStatus update(double delta_time_ms) override { return update_status_; };
  void loadScene() override;
  void unloadScene() override {}

 private:
  void generateMap();
  void generateInteractionEvent();
  void renderInteractionOverlay(
      std::shared_ptr<common::twod::RendererManager> renderer_manager);

  UpdateStatus update_status_;
  std::vector<MapNode> nodes_;
  MapState state_;
  InteractionEvent current_event_;
};
}  // namespace map
}  // namespace scenes

#endif  // SCENES_MAP_MAP_SCENE_H_
