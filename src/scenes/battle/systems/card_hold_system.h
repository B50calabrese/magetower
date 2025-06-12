#ifndef CARD_HOLD_SYSTEM_H
#define CARD_HOLD_SYSTEM_H

#include "common/ecs/engine.h"
#include "common/ecs/event.h"
#include "common/ecs/event_listener.h"
#include "common/ecs/system.h"
#include "core/events/mouse_click_event.h"

namespace scenes {
namespace battle {
namespace systems {

/*
 * This system is responsible for managing the card the player is holding.
 */
class CardHoldSystem : public common::ecs::System,
                       public common::ecs::EventListener {
 public:
  CardHoldSystem();

  void process(common::ecs::Engine& engine, double delta_time_ms);

  void registerEventListeners(common::ecs::Engine& engine) override {
    engine.registerEventListener<core::events::MouseClickEvent>(this);
  }

  bool handleEvent(common::ecs::Event& event, common::ecs::Engine& engine);
};

}  // namespace systems
}  // namespace battle
}  // namespace scenes

#endif  // CARD_HOLD_SYSTEM_H