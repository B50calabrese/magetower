#ifndef ANIMATION_STATE_COMPONENT_H
#define ANIMATION_STATE_COMPONENT_H

#include <memory>

#include "common/ecs/component.h"

namespace core {
    namespace components {

        /**
        * Singleton component used to communicate to the rest of the systems that an animation is playing or not.
        */
        class AnimationStateComponent : public common::ecs::Component {
        public:
            AnimationStateComponent() : is_animation_playing(false) {}

            std::unique_ptr<Component> clone() const override {
                return std::make_unique<AnimationStateComponent>();
            }

            int getComponentIdInstance() const override {
                return Component::getComponentId<AnimationStateComponent>();
            }

            bool isAnimationPlaying() const {
                return this->is_animation_playing;
            }

            void setIsAnimationPlaying(bool is_animation_playing) {
                this->is_animation_playing = is_animation_playing;
            }

        private:
            bool is_animation_playing;
        };

    } // namespace components
} // namespace core

#endif // MOUSE_POSITION_COMPONENT_H