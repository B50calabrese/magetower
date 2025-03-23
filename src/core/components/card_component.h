#ifndef CARD_COMPONENT_H
#define CARD_COMPONENT_H

#include <string>

#include "common/ecs/component.h"
#include "common/resources/texture.h"

namespace core {
    namespace components {

        /*
        * Defines the general data required of all 'cards'.
        */
        class CardComponent : public common::ecs::Component {
        public:
            CardComponent(std::string name) : name(name), is_visible(true), is_hovered(false), is_faceup(false) {}

            CardComponent(common::resources::Texture card_art_texture, std::string name) :
              name(name), is_visible(true), is_hovered(false), is_faceup(false), card_art_texture(card_art_texture) {}

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

            bool isFaceup() {
                return this->is_faceup;
            }

            void setIsFaceup(bool is_faceup) {
                this->is_faceup = is_faceup;
            }

            common::resources::Texture& getCardArtTexture() {
                return this->card_art_texture;
            }

            void setCardArtTexture(common::resources::Texture texture) {
                this->card_art_texture = texture;
            }

        private:
            std::string name;
            bool is_visible;
            bool is_hovered;
            bool is_faceup;

            common::resources::Texture card_art_texture;
        };

    } // namespace components
} // namespace core

#endif // CARD_COMPONENT_H