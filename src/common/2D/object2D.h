#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "glm/vec2.hpp"

namespace common {
    namespace twod {

        /*
        * An Object2D represents a generic 'object' with size, position, and rotation.
        */
        class Object2D {
        public:
            Object2D() : position(0.0f), size(0.0f), scale(1.0f), rotation_radians(0.0f) {}
            Object2D(glm::vec2 position, glm::vec2 size, glm::vec2 scale)
                : position(position), size(size), scale(scale), rotation_radians(0.0f) {}

            void setPosition(glm::vec2 position) {
                this->position = position;
            }

            glm::vec2 getPosition() {
                return this->position;
            }

            void setSize(glm::vec2 size) {
                this->size = size;
            }

            glm::vec2 getSize() {
                return this->size;
            }

            void setScale(glm::vec2 scale) {
                this->scale= scale;
            }

            glm::vec2 getScale() {
                return this->scale;
            }

            void setRotationRadians(float radians) {
                this->rotation_radians = radians;
            }

            float getRotationRadians() {
                return this->rotation_radians;
            }

            bool containsPoint(glm::vec2 point);

        private:
            glm::vec2 position;
            glm::vec2 size;
            glm::vec2 scale;
            float rotation_radians;
        };
    } // namespace twod
} // namespace common

#endif // OBJECT2D_H