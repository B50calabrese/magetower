#ifndef MOUSE_CLICK_EVENT_H
#define MOUSE_CLICK_EVENT_H

#include "common/ecs/event.h"

namespace core {
namespace events {

class MouseClickEvent : public common::ecs::Event {
 public:
  std::string getName() const { return "MouseClickEvent"; }

  bool shouldConsumeOnFirstPass() override { return true; }
};

}  // namespace events
}  // namespace core

#endif  // MOUSE_CLICK_EVENT_H