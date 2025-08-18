#ifndef COMMON_ECS_ENGINE_H_
#define COMMON_ECS_ENGINE_H_

#include <map>
#include <memory>
#include <queue>
#include <typeindex>
#include <vector>

#include "common/2D/renderer_manager.h"
#include "entity.h"
#include "event.h"
#include "event_listener.h"
#include "render_system.h"
#include "system.h"

namespace common {
namespace ecs {

/* Manager of the ecs system, handles the coordination of the different parts.
 */
class Engine {
 public:
  using EntityList = std::vector<std::shared_ptr<Entity>>;
  using SystemsList = std::vector<std::unique_ptr<System>>;
  using RenderSystemsList = std::vector<std::unique_ptr<RenderSystem>>;
  using EventQueue = std::queue<std::shared_ptr<Event>>;
  using EventListenersList = std::vector<EventListener*>;
  using EventTypeToListenersMap = std::map<std::type_index, EventListenersList>;
  using SingletonComponentMap =
      std::map<std::type_index, std::unique_ptr<Component>>;

  Engine() = default;
  ~Engine() = default;

  const EntityList& getEntities() const { return entities_; }

  const std::shared_ptr<Entity> getEntityFromId(int id) const;

  Entity& newEntity();

  /*
   * Registers a given system with the given arguments.
   */
  template <typename T, typename... Args>
  void registerSystem(Args&&... args) {
    std::unique_ptr<T> system =
        std::make_unique<T>(std::forward<Args>(args)...);
    systems_.push_back(std::move(system));
    systems_.back()->registerEventListeners(*this);
  }

  /*
   * Registers a given render system with the given arguments.
   */
  template <typename T, typename... Args>
  void registerRenderSystem(Args&&... args) {
    std::unique_ptr<T> system =
        std::make_unique<T>(std::forward<Args>(args)...);
    render_systems_.push_back(std::move(system));
  }

  void runSystems(double delta_time_ms);

  void runRenderSystems(
      std::shared_ptr<common::twod::RendererManager> renderer_manager);

  void publishEvent(std::unique_ptr<Event> event);

  /*
   * Used to register an event listener, using the event as a template type.
   */
  template <typename EventType>
  void registerEventListener(EventListener* event_listener) {
    std::type_index eventTypeIndex = std::type_index(typeid(EventType));
    event_type_to_listeners_map_[eventTypeIndex].push_back(event_listener);
  }

  /*
   * Registers a singleton component in the world.
   */
  template <typename T, typename... Args>
  T& registerSingletonComponent(Args&&... args);

  /*
   * Return the singleton component registered in the world.
   */
  template <typename T>
  T* getSingletonComponent() const;

 private:
  static int kNumberOfEntities;

  EntityList entities_;
  SystemsList systems_;
  RenderSystemsList render_systems_;
  EventQueue event_queue_;
  EventTypeToListenersMap event_type_to_listeners_map_;
  SingletonComponentMap singleton_component_map_;
};

}  // namespace ecs
}  // namespace common

#endif  // COMMON_ECS_ENGINE_H_