#include "animation_system.h"

#include "common/utils/math.h"
#include "core/components/animation_component.h"
#include "core/components/position_component.h"

namespace core {
    namespace systems {

        using common::ecs::Engine;
        using core::components::AnimationComponent;
        using core::components::PositionComponent;

        AnimationSystem::AnimationSystem() {
            this->setRequiredComponent<AnimationComponent>();
            this->setRequiredComponent<PositionComponent>();
        }

        void AnimationSystem::process(Engine& engine, double delta_time_ms) {
            for (auto& entity : engine.getEntities()) {
                if ((this->getRequiredSignature() & entity->getSignature()) == this->getRequiredSignature()) {
                    AnimationComponent* animation_component = entity->getComponent<AnimationComponent>();
                    PositionComponent* position_component = entity->getComponent<PositionComponent>();

                    if (animation_component->getAnimationState() != AnimationComponent::ANIMATING) {
                        continue;
                    }

                    animation_component->addElapsedMs(delta_time_ms);

                    if (animation_component->getElapsedMs() >= animation_component->getDurationMs()) {
                        // The animation is completed, time to clean up.
                        position_component->setPosition(animation_component->getEndingPosition());
                        animation_component->setAnimationState(AnimationComponent::FINISHED);

                        // If there is a callback, then let's call it.
                        if (animation_component->getCallbackFunction()) {
                            animation_component->getCallbackFunction()(engine, entity->getId());
                        }

                        entity->removeComponent<AnimationComponent>();
                    }
                    else {
                        // Update the positions.
                        position_component->setX(
                            common::utils::tween(
                                animation_component->getStartingPosition().x,
                                animation_component->getEndingPosition().x,
                                animation_component->getElapsedMs() / animation_component->getDurationMs()));

                        position_component->setY(
                            common::utils::tween(
                                animation_component->getStartingPosition().y,
                                animation_component->getEndingPosition().y,
                                animation_component->getElapsedMs() / animation_component->getDurationMs()));
                    }
                }
            }
        }

    } // namespace systems
} // namespace core