#ifndef CONSTS_H
#define CONSTS_H

namespace core {
    // UI constants
    const static float SCREEN_WIDTH = 1920.0f;
    const static float SCREEN_HEIGHT = 1080.0f;
    const static glm::vec2 SCREEN_SIZE = glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);

    const static float HALF_SCREEN_WIDTH = SCREEN_WIDTH / 2.0f;
    const static float HALF_SCREEN_HEIGHT = SCREEN_HEIGHT / 2.0f;

    // Scene IDs
    const static int MAIN_MENU_SCENE_ID = 1;
    const static int BATTLE_SCENE_ID = 2;
} // namespace core

#endif // CONSTS_H