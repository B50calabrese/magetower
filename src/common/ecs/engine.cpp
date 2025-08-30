#include "engine.h"

#include <iostream>

#include "common/utils/logger.h"

namespace common {
namespace ecs {

int Engine::kNumberOfEntities = 0;

const std::shared_ptr<Entity> Engine::getEntityFromId(int id) const {
  for (auto entity : entities_) {
    if (entity->getId() == id) {
      return entity;
    }
  }
  return nullptr;
}

Entity& Engine::newEntity() {
  std::shared_ptr<Entity> entity =
      std::make_shared<Entity>(kNumberOfEntities++);
  entities_.push_back(std::move(entity));
  return *(entities_.back());
}

void Engine::runSystems(double delta_time_ms) {
  // Handle just the first event if it exists.
  if (!event_queue_.empty()) {
    std::shared_ptr<Event> event = event_queue_.front();
    utils::Logger::Info("Processing event: " + event->getName());
    // Get the listeners for the given event type.
    std::type_index eventTypeIndex = std::type_index(typeid(*event));
    auto listeners = event_type_to_listeners_map_.find(eventTypeIndex);

    bool should_pop_event = event->shouldConsumeOnFirstPass();
    // If we have any listeners to iterate through then do so.
    if (listeners != event_type_to_listeners_map_.end()) {
      for (auto& listener : listeners->second) {
        if (listener->handleEvent(*event, *this)) {
          should_pop_event = true;
          break;
        }
      }
    } else {
      utils::Logger::Info("No event listeners subscribed for event type: " +
                          event->getName());
    }

    if (should_pop_event) {
      event_queue_.pop();
    }
  }

  // Once events are processed then finish.
  for (const auto& system : systems_) {
    system->process(*this, delta_time_ms);
  }
}

void Engine::runRenderSystems(
    std::shared_ptr<common::twod::RendererManager> renderer_manager) {
  for (const auto& system : render_systems_) {
    system->render(*this, renderer_manager);
  }
}

void Engine::publishEvent(std::unique_ptr<Event> event) {
  event_queue_.push(std::move(event));
}

}  // namespace ecs
}  // namespace common