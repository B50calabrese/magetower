#ifndef PLAYER_DECK_SYSTEM_H
#define PLAYER_DECK_SYSTEM_H

#include "common/ecs/engine.h"
#include "common/ecs/event.h"
#include "common/ecs/event_listener.h"
#include "common/ecs/system.h"
#include "scenes/battle/events/player_draw_card_start_event.h"

namespace scenes {
namespace battle {
namespace systems {

class PlayerDeckSystem : public common::ecs::System,
                         public common::ecs::EventListener {
 public:
  PlayerDeckSystem();

  void process(common::ecs::Engine& engine, double delta_time_ms);

  void registerEventListeners(common::ecs::Engine& engine) override {
    engine.registerEventListener<
        scenes::battle::events::PlayerDrawCardStartEvent>(this);
  }

  bool handleEvent(common::ecs::Event& event, common::ecs::Engine& engine);
};

}  // namespace systems
}  // namespace battle
}  // namespace scenes

#endif  // PLAYER_DECK_SYSTEM_H