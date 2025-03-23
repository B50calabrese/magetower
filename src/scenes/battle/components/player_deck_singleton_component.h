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

                void addCard(int id) {
                    this->deck.push_back(id);
                }

                int getSizeOfDeck() {
                    return this->deck.size();
                }

                std::vector<int> getDeck() {
                    return this->deck;
                }

            private:
                // Contains a reference id to all the entities that make up this deck.
                std::vector<int> deck;
            };
        } // namespace components
    } // namespace battle
} // namespace scenes

#endif // PLAYER_DECK_SINGLETON_COMPONENT_H