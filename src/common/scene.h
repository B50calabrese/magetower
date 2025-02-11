#ifndef SCENE_H
#define SCENE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace common {

	/**
	* Represents a single 'screen' of a game. The business and rendering logic should be encapsulated in this individual scene.
	*/
	class Scene {
	public:
		Scene(int id) : id(id) {}

		enum UpdateStatus {
			OK,
			CLOSE_WINDOW
		};

		virtual void render() = 0;
		virtual UpdateStatus update(float deltaTime) = 0;
		virtual void processInput(GLFWwindow* window) = 0;
		virtual void processMouseInput(GLFWwindow* window, double xPos, double yPos) = 0;
		virtual void processMouseClick(GLFWwindow* window, int button, int action, int mods) = 0;
		virtual void loadScene() = 0;

		int getId() {
			return this->id;
		}
	private:
		int id;
	};

} // namespace common

#endif // SCENE_H