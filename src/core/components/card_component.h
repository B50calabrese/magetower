#ifndef CARD_COMPONENT_H
#define CARD_COMPONENT_H

#include <string>

#include "common/ecs/component.h"

namespace core {
    namespace components {

        /*
        * Defines the general data required of all 'cards'.
        */
        class CardComponent : public common::ecs::Component {
        public:
            CardComponent(std::string name) : name(name), is_visible(false) {}

            std::string getName() {
                return this->name;
            }

            void setName(std::string name) {
                this->name = name;
            }

            bool isVisible() {
                return this->is_visible;
            }

            void setIsVisible(bool is_visible) {
                this->is_visible = is_visible;
            }

        private:
            std::string name;
            bool is_visible;
            bool is_hovered;
        };

    } // namespace components
} // namespace core

#endif // CARD_COMPONENT_H