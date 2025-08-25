#ifndef SCENES_MAINMENU_MAIN_MENU_SCENE_H_
#define SCENES_MAINMENU_MAIN_MENU_SCENE_H_

#include <memory>

#include "common/2D/sprite.h"
#include "common/scene.h"
#include "core/consts.h"
#include "core/scene_ids.h"

namespace scenes {
namespace mainmenu {

class MainMenuScene : public common::Scene {
 public:
  MainMenuScene()
      : Scene(static_cast<int>(core::SceneId::MainMenu)),
        update_status_(UpdateStatus::kOk) {}

  void render(
      std::shared_ptr<common::twod::RendererManager> renderer_manager) override;
  void processMouseInput(GLFWwindow* window, double x_pos,
                         double y_pos) override {
    mouse_position_ = convertMousePositionIntoScreenCoordinates(
        x_pos, y_pos, core::SCREEN_WIDTH, core::SCREEN_HEIGHT);
  }
  void processMouseClick(GLFWwindow* window, int button, int action,
                         int mods) override;
  void processKeyInput(GLFWwindow* window, int key, int scancode, int action,
                       int mod) override {}
  UpdateStatus update(double delta_time_ms) override { return update_status_; };
  void loadScene() override;
  void unloadScene() override {}

 private:
  UpdateStatus update_status_;
  common::resources::Texture* background_texture_;
  std::shared_ptr<common::twod::Sprite> start_button_;
  std::shared_ptr<common::twod::Sprite> exit_button_;
};
}  // namespace mainmenu
}  // namespace scenes

#endif  // SCENES_MAINMENU_MAIN_MENU_SCENE_H_