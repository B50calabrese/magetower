#include "main_menu_scene.h"

#include <iostream>

#include "common/resources/resource_manager.h"

namespace scenes {
    namespace mainmenu {

        using common::resources::ResourceManager;

        void MainMenuScene::render(std::shared_ptr<common::twod::RendererManager> renderer_manager) {
            renderer_manager->getSpriteRenderer()->DrawSprite(this->background_texture, glm::vec2(0.0f, 0.0f), glm::vec2(1000.0f, 1000.0f));
        }

        void MainMenuScene::loadScene() {
            this->background_texture = ResourceManager::LoadTextureRelative("assets/mainmenu/background.png", "main_menu_background", /*alpha=*/ false);
        }

    } // namespace mainmenu
} // namespace scenes