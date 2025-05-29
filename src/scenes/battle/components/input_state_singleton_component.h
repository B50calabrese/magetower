#ifndef INPUT_STATE_SINGLETON_COMPONENT_H
#define INPUT_STATE_SINGLETON_COMPONENT_H

#include <memory>

#include "common/ecs/component.h"

namespace scenes {
    namespace battle {
        namespace components {

            /*
            * A singleton component to hold the current state for user controlled input.
            */
            class InputStateSingletonComponent : public common::ecs::Component {
            public:
                InputStateSingletonComponent() {
                    this->input_state = InputState::FULL_CONTROL;
                }

                std::unique_ptr<Component> clone() const override {
                    return std::make_unique<InputStateSingletonComponent>();
                }

                int getComponentIdInstance() const override {
                    return Component::getComponentId<InputStateSingletonComponent>();
                }

                enum InputState {
                    FULL_CONTROL,
                    PLAYER_HOLDING_CARD
                };

                InputState getInputState() {
                    return this->input_state;
                }

                void setInputState(InputState input_state) {
                    this->input_state = input_state;
                }

            private:
                InputState input_state;
            };
        }
    }
}

#endif // INPUT_STATE_SINGLETON_COMPONENT_H