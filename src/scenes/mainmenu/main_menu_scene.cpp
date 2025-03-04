#include "main_menu_scene.h"

#include <iostream>

#include "common/2D/sprite.h"
#include "common/resources/resource_manager.h"
#include "common/resources/texture.h"
#include "core/consts.h"

namespace scenes {
    namespace mainmenu {

        using common::twod::Sprite;
        using common::resources::ResourceManager;
        using common::resources::Texture;

        void MainMenuScene::render(std::shared_ptr<common::twod::RendererManager> renderer_manager) {
            auto sprite_renderer = renderer_manager->getSpriteRenderer();
            // Render the background.
            sprite_renderer->DrawSprite(this->background_texture, glm::vec2(0.0f, 0.0f), this->background_texture.getSizeVector());

            // Render the buttons.
            start_button->render(renderer_manager);
            exit_button->render(renderer_manager);
        }

        void MainMenuScene::processMouseClick(GLFWwindow* window, int button, int action, int mods) {
            // If clicked, check interaction with our buttons on the screen.
            if (this->wasLeftButtonClicked(button, action)) {
                if (this->start_button->containsPoint(this->mouse_position)) {
                    // Switch scene
                    this->update_status = UpdateStatus::SWITCH_SCENE;
                    this->next_scene_id = core::BATTLE_SCENE_ID;
                } else if (this->exit_button->containsPoint(this->mouse_position)) {
                    this->update_status = UpdateStatus::CLOSE_WINDOW;
                }
            }
        }

        void MainMenuScene::loadScene() {
            this->background_texture = ResourceManager::LoadTextureRelative("assets/mainmenu/background.png", "main_menu_background", /*alpha=*/ true);
            
            Texture start_button_texture = ResourceManager::LoadTextureRelative("assets/mainmenu/start_game_button.png", "start_game_button", /*alpha=*/ true);
            this->start_button = std::make_shared<Sprite>(
                start_button_texture,
                glm::vec2(core::HALF_SCREEN_WIDTH - (start_button_texture.getWidth() / 2), core::HALF_SCREEN_HEIGHT),
                start_button_texture.getSizeVector());
            
            Texture exit_button_texture = ResourceManager::LoadTextureRelative("assets/mainmenu/exit_game_button.png", "exit_game_button", /*alpha=*/ true);
            this->exit_button = std::make_shared<Sprite>(
                exit_button_texture,
                glm::vec2(core::HALF_SCREEN_WIDTH - (exit_button_texture.getWidth() / 2), core::HALF_SCREEN_HEIGHT - exit_button_texture.getHeight()),
                exit_button_texture.getSizeVector());
        }

    } // namespace mainmenu
} // namespace scenes