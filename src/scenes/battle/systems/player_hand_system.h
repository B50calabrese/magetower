#ifndef PLAYER_HAND_SYSTEM
#define PLAYER_HAND_SYSTEM

#include "common/ecs/engine.h"
#include "common/ecs/event.h"
#include "common/ecs/event_listener.h"
#include "common/ecs/system.h"
#include "core/events/mouse_click_event.h"
#include "scenes/battle/events/player_hand_update_event.h"

namespace scenes {
namespace battle {
namespace systems {

/*
 * This system is responsible for managing the players hand.
 */
class PlayerHandSystem : public common::ecs::System,
                         public common::ecs::EventListener {
 public:
  PlayerHandSystem();

  void process(common::ecs::Engine& engine, double delta_time_ms);

  void registerEventListeners(common::ecs::Engine& engine) override {
    engine.registerEventListener<scenes::battle::events::PlayerHandUpdateEvent>(
        this);
    engine.registerEventListener<core::events::MouseClickEvent>(this);
  }

  bool handleEvent(common::ecs::Event& event, common::ecs::Engine& engine);

 private:
  // The speed at which to scale up or scale down a card that is hovered.
  const static int SCALE_SPEED_WIDTH;
  const static int SCALE_SPEED_HEIGHT;

  void updateHandSizeAndPosition(common::ecs::Engine& engine);

  bool handlePlayerClickedEvent(common::ecs::Engine& engine);
};

}  // namespace systems
}  // namespace battle
}  // namespace scenes

#endif  // PLAYER_HAND_SYSTEM