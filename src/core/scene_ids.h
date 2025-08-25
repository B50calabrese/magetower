#ifndef SCENE_IDS_H
#define SCENE_IDS_H

namespace core {

// Represents a specific scene in the game.
enum class SceneId : unsigned int {
  MainMenu = 1,
  Battle = 2,
  Map = 3,
  Shop = 4,
  INVALID = -1
};

}  // namespace core

#endif  // SCENE_IDS_H