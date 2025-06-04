#ifndef PLAYER_DECK_SINGLETON_COMPONENT_H
#define PLAYER_DECK_SINGLETON_COMPONENT_H

#include <memory>
#include <vector>

#include "common/ecs/component.h"
#include "common/ecs/entity.h"

namespace scenes {
    namespace battle {
        namespace components {

            /*
            * Contains references to entities that comprise the player's deck.
            */
            class PlayerDeckSingletonComponent : public common::ecs::Component {
            public:
                PlayerDeckSingletonComponent() = default;

                std::unique_ptr<Component> clone() const override {
                    return std::make_unique<PlayerDeckSingletonComponent>();
                }

                int getComponentIdInstance() const override {
                    return Component::getComponentId<PlayerDeckSingletonComponent>();
                }

                void addCard(int id) {
                    this->deck.push_back(id);
                }

                int getSizeOfDeck() const {
                    return this->deck.size();
                }

                std::vector<int> getDeck() {
                    return this->deck;
                }

                int drawCard() {
                    int id = this->deck[0];
                    this->deck.erase(this->deck.begin());
                    return id;
                }

            private:
                // Contains a reference id to all the entities that make up this deck.
                std::vector<int> deck;
            };
        } // namespace components
    } // namespace battle
} // namespace scenes

#endif // PLAYER_DECK_SINGLETON_COMPONENT_H