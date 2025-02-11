#ifndef SCENE_H
#define SCENE_H

namespace common {

	class Screen {
	public:
		enum UpdateStatus {
			OK,
			CLOSE_WINDOW
		};

		virtual void render() = 0;
		virtual UpdateStatus update(float deltaTime) = 0;
		virtual void processInput(GLFWwindow* window) = 0;
		virtual void processMouseInput(GLFWwindow* window, double xPos, double yPos) = 0;
		virtual void processMouseClick(GLFWwindow* window, int button, int action, int mods) = 0;
		virtual void loadScreen() = 0;
	};

} // namespace common

#endif // SCENE_H