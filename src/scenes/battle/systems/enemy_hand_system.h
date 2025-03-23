#ifndef ENEMY_HAND_SYSTEM_H
#define ENEMY_HAND_SYSTEM_H

#include "common/ecs/engine.h"
#include "common/ecs/event.h"
#include "common/ecs/event_listener.h"
#include "common/ecs/system.h"

namespace scenes {
    namespace battle {
        namespace systems {

            /*
            * This system is responsible for managing the enemy's hand.
            */
            class EnemyHandSystem : public common::ecs::System, public common::ecs::EventListener {
            public:
                EnemyHandSystem();

                void process(common::ecs::Engine& engine);

                void registerEventListeners(common::ecs::Engine& engine) override {
                }

                bool handleEvent(common::ecs::Event& event, common::ecs::Engine& engine);

            private:
            };

        } // namespace systems
    } // namespace battle
} // namespace scenes

#endif // ENEMY_HAND_SYSTEM_H