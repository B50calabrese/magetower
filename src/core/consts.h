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

    // Card constants
    const static float CARD_DEFAULT_WIDTH = 196.0f;
    const static float CARD_DEFAULT_HEIGHT = 256.0f;

    const static int CARD_IN_HAND_WIDTH = 96;
    const static int CARD_IN_HAND_HEIGHT = 128;
    const static int CARD_IN_HAND_ZOOM_SCALE = 2;
    const static int CARD_IN_HAND_ZOOM_WIDTH = CARD_IN_HAND_WIDTH * CARD_IN_HAND_ZOOM_SCALE;
    const static int CARD_IN_HAND_ZOOM_HEIGHT = CARD_IN_HAND_HEIGHT * CARD_IN_HAND_ZOOM_SCALE;

    const static int CARD_HOLDING_WIDTH = 144;
    const static int CARD_HOLDING_HALF_WIDTH = CARD_HOLDING_WIDTH / 2;
    const static int CARD_HOLDING_HEIGHT = 196;
    const static int CARD_HOLDING_HALF_HEIGHT = CARD_HOLDING_HEIGHT / 2;
} // namespace core

#endif // CONSTS_H