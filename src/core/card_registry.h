#ifndef CARD_REGISTRY_H
#define CARD_REGISTRY_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "common/ecs/component.h"

namespace core {

    /*
    * Container class that contains references to all the cards possible in the game. Makes it easier
    * to create cards on the fly for construction of the deck/rendering.
    */
    class CardRegistry {
    public:
        using CardPrototype = std::vector<std::unique_ptr<common::ecs::Component>>;

        CardRegistry();

        CardPrototype getCardPrototype(int card_id);

        void addCard(int card_id, std::vector<std::shared_ptr<common::ecs::Component>> components);

    private:
        std::map<int, CardPrototype> card_prototypes;

        void initRegistry();

        void addCard(int card_id, std::string card_name, std::string card_art_name);
    };

} // namespace core

#endif // CARD_REGISTRY_H