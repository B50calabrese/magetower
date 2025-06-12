#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <functional>
#include <memory>
#include <string>

#include "common/ecs/component.h"
#include "common/ecs/engine.h"
#include "common/resources/texture.h"

namespace core {
namespace components {

/*
 * Tracks an animation of an entity, including the callback function for the end
 * of the animation.
 */
class AnimationComponent : public common::ecs::Component {
 public:
  using AnimationCallbackFunction =
      std::function<void(common::ecs::Engine&, int entity_id)>;

  AnimationComponent(glm::vec2 starting_position, glm::vec2 ending_position,
                     float duration_ms)
      : starting_position(starting_position),
        ending_position(ending_position),
        animation_state(AnimationState::NOT_STARTED),
        duration_ms(duration_ms),
        elapsed_ms(0.0f),
        callback_ptr(nullptr) {}

  std::unique_ptr<Component> clone() const override {
    return std::make_unique<AnimationComponent>(
        this->starting_position, this->ending_position, this->duration_ms);
  }

  int getComponentIdInstance() const override {
    return Component::getComponentId<AnimationComponent>();
  }

  enum AnimationState { NOT_STARTED, ANIMATING, FINISHED };

  AnimationState getAnimationState() const { return this->animation_state; }

  void setAnimationState(AnimationState animation_state) {
    this->animation_state = animation_state;
  }

  void addElapsedMs(float elapsed) { this->elapsed_ms += elapsed; }

  float getElapsedMs() const { return this->elapsed_ms; }

  float getDurationMs() const { return this->duration_ms; }

  void setCallbackFunction(AnimationCallbackFunction callback_ptr) {
    this->callback_ptr = callback_ptr;
  }

  AnimationCallbackFunction getCallbackFunction() const {
    return this->callback_ptr;
  }

  glm::vec2 getStartingPosition() const { return this->starting_position; }

  glm::vec2 getEndingPosition() const { return this->ending_position; }

 private:
  AnimationState animation_state;
  float duration_ms, elapsed_ms;
  glm::vec2 starting_position, ending_position;
  AnimationCallbackFunction callback_ptr;
};

}  // namespace components
}  // namespace core

#endif  // CARD_COMPONENT_H