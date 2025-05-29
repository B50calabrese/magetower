#ifndef SIZE_COMPONENT_H
#define SIZE_COMPONENT_H

#include <memory>

#include "common/ecs/component.h"

namespace core {
    namespace components {

        class SizeComponent : public common::ecs::Component {
        public:
            SizeComponent(int width, int height) : width(width), height(height) {}

            std::unique_ptr<Component> clone() const override {
                return std::make_unique<SizeComponent>(this->width, this->height);
            }

            int getComponentIdInstance() const override {
                return Component::getComponentId<SizeComponent>();
            }

            int getWidth() {
                return this->width;
            }

            void setWidth(int width) {
                this->width = width;
            }

            int getHeight() {
                return this->height;
            }

            void setHeight(int height) {
                this->height = height;
            }

            void setSize(int width, int height) {
                this->width = width;
                this->height = height;
            }

            glm::vec2 getSizeVec() {
                return glm::vec2(width, height);
            }

        private:
            int width, height;
        };

    } // namespace components
} // namespace core

#endif // SIZE_COMPONENT_H