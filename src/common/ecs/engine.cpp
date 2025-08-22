#include "common/ecs/engine.h"

#include <iostream>

#include "common/utils/logger.h"

namespace common {
namespace ecs {

int Engine::kNumberOfEntities = 0;

const std::shared_ptr<Entity> Engine::GetEntityFromId(int id) const {
  for (auto entity : entities_) {
    if (entity->id() == id) {
      return entity;
    }
  }
  return nullptr;
}

Entity& Engine::NewEntity() {
  std::shared_ptr<Entity> entity =
      std::make_shared<Entity>(kNumberOfEntities++);
  entities_.push_back(std::move(entity));
  return *(entities_.back());
}

void Engine::RunSystems(double delta_time_ms) {
  // Handle just the first event if it exists.
  if (!event_queue_.empty()) {
    std::shared_ptr<Event> event = event_queue_.front();
    utils::Logger::Info("Processing event: " + event->name());
    // Get the listeners for the given event type.
    std::type_index eventTypeIndex = std::type_index(typeid(*event));
    auto listeners = event_type_to_listeners_map_.find(eventTypeIndex);

    bool should_pop_event = event->ShouldConsumeOnFirstPass();
    // If we have any listeners to iterate through then do so.
    if (listeners != event_type_to_listeners_map_.end()) {
      for (auto& listener : listeners->second) {
        if (listener->HandleEvent(*event, *this)) {
          should_pop_event = true;
          break;
        }
      }
    } else {
      utils::Logger::Info("No event listeners subscribed for event type: " +
                          event->name());
    }

    if (should_pop_event) {
      event_queue_.pop();
    }
  }

  // Once events are processed then finish.
  for (const auto& system : systems_) {
    system->Process(*this, delta_time_ms);
  }
}

void Engine::RunRenderSystems(
    std::shared_ptr<common::twod::RendererManager> renderer_manager) {
  for (const auto& system : render_systems_) {
    system->Render(*this, renderer_manager);
  }
}

void Engine::PublishEvent(std::unique_ptr<Event> event) {
  event_queue_.push(std::move(event));
}

template <typename T, typename... Args>
T& Engine::RegisterSingletonComponent(Args&&... args) {
  std::type_index typeIndex = std::type_index(typeid(T));
  if (singleton_component_map_.count(typeIndex)) {
    utils::Logger::Warning("Singleton Component of type already registered: " +
                         std::string(typeIndex.name()));
    return *static_cast<T*>(singleton_component_map_[typeIndex].get());
  }
  std::unique_ptr<T> component =
      std::make_unique<T>(std::forward<Args>(args)...);
  singleton_component_map_[typeIndex] = std::move(component);
  return *static_cast<T*>(singleton_component_map_[typeIndex].get());
}

template <typename T>
T* Engine::GetSingletonComponent() const {
  std::type_index typeIndex = std::type_index(typeid(T));
  if (singleton_component_map_.count(typeIndex)) {
    return static_cast<T*>(singleton_component_map_.at(typeIndex).get());
  }
  return nullptr;  // Return nullptr if singleton component is not registered
}

}  // namespace ecs
}  // namespace common