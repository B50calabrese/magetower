#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common/2D/renderer_manager.h"

namespace common {

	/**
	* Represents a single 'screen' of a game. The business and rendering logic should be encapsulated in this individual scene.
	*/
	class Scene {
	public:
		Scene(int id) : id(id), mouse_position(0.0f), next_scene_id(0) {}

		enum UpdateStatus {
			OK,
			CLOSE_WINDOW,
			SWITCH_SCENE
		};

		virtual void render(std::shared_ptr<common::twod::RendererManager> renderer_manager) = 0;
		virtual UpdateStatus update(float delta_time_ms) = 0;
		virtual void processMouseInput(GLFWwindow* window, double xPos, double yPos) = 0;
		virtual void processMouseClick(GLFWwindow* window, int button, int action, int mods) = 0;
		virtual void loadScene() = 0;
		virtual void unloadScene() = 0;

		int getId() {
			return this->id;
		}

		int getNextSceneId() {
			return this->next_scene_id;
		}

	protected:
		bool wasLeftButtonClicked(const int button, const int action) {
			return (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS);
		}

		glm::vec2 convertMousePositionIntoScreenCoordinates(double xPos, double yPos, float screen_width, float screen_height) {
			return glm::vec2(xPos, screen_height - yPos);
		}

		glm::vec2 mouse_position;
		int next_scene_id;

	private:
		int id;
	};

} // namespace common

#endif // SCENE_H