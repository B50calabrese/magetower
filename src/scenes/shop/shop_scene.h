#ifndef SCENES_SHOP_SHOP_SCENE_H_
#define SCENES_SHOP_SHOP_SCENE_H_

#include <memory>
#include <vector>

#include "common/2D/sprite.h"
#include "common/ecs/entity.h"
#include "common/scene.h"
#include "core/card_registry.h"
#include "core/renderutils/card_render_util.h"
#include "core/scene_ids.h"

namespace scenes {
namespace shop {

class ShopScene : public common::Scene {
 public:
  ShopScene()
      : common::Scene(static_cast<int>(core::SceneId::Shop)),
        update_status_(UpdateStatus::kOk) {}

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
  UpdateStatus update_status_;
  std::vector<common::ecs::Entity> cards_in_shop_;
  core::CardRegistry card_registry_;
  std::unique_ptr<core::renderutils::CardRenderUtil> card_render_util_;
  std::shared_ptr<common::twod::Sprite> leave_button_;
};
}  // namespace shop
}  // namespace scenes

#endif  // SCENES_SHOP_SHOP_SCENE_H_
