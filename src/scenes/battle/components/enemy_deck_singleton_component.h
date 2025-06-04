#ifndef ENEMY_DECK_SINGLETON_COMPONENT_H
#define ENEMY_DECK_SINGLETON_COMPONENT_H

#include <memory>
#include <vector>

#include "common/ecs/component.h"
#include "common/ecs/entity.h"

namespace scenes {
    namespace battle {
        namespace components {

            /*
            * Contains references to entities that comprise the enemy's deck.
            */
            class EnemyDeckSingletonComponent : public common::ecs::Component {
            public:
                EnemyDeckSingletonComponent() = default;

                std::unique_ptr<Component> clone() const override {
                    return std::make_unique<EnemyDeckSingletonComponent>();
                }

                int getComponentIdInstance() const override {
                    return Component::getComponentId<EnemyDeckSingletonComponent>();
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