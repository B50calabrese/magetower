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
            CardComponent(std::string name) : name(name) {}

            std::string getName() {
                return this->name;
            }

            void setName(std::string name) {
                this->name = name;
            }

        private:
            std::string name;
        };

    } // namespace components
} // namespace core

#endif // CARD_COMPONENT_H