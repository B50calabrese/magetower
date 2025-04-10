#ifndef MOUSE_POSITION_COMPONENT_H
#define MOUSE_POSITION_COMPONENT_H

#include <glm/ext/vector_float2.hpp>

#include "common/ecs/component.h"

namespace core {
    namespace components {

        class MousePositionComponent : public common::ecs::Component {
        public:
            MousePositionComponent(float x, float y) : x(x), y(y) {}

            float getX() {
                return this->x;
            }

            float getY() {
                return this->y;
            }

            glm::vec2 getPosition() {
                return glm::vec2(this->x, this->y);
            }

            void setX(float x) {
                this->x = x;
            }

            void setY(float y) {
                this->y = y;
            }

        private:
            float x, y;
        };

    } // namespace components
} // namespace core

#endif // MOUSE_POSITION_COMPONENT_H