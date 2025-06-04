#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include <glm/vec2.hpp>
#include <memory>

#include "common/ecs/component.h"

namespace core {
    namespace components {

        class PositionComponent : public common::ecs::Component {
        public:
            PositionComponent(glm::vec2 position) : position(position) {}

            std::unique_ptr<Component> clone() const override {
                return std::make_unique<PositionComponent>(this->position);
            }

            int getComponentIdInstance() const override {
                return Component::getComponentId<PositionComponent>();
            }

            glm::vec2 getPosition() const {
                return this->position;
            }

            void setPosition(glm::vec2 position) {
                this->position = position;
            }

            float getX() const {
                return this->position.x;
            }

            void setX(float x) {
                this->position.x = x;
            }

            float getY() const {
                return this->position.y;
            }

            void setY(float y) {
                this->position.y = y;
            }

        private:
            glm::vec2 position;
        };

    } // namespace components
} // namespace core

#endif // POSITION_COMPONENT_H