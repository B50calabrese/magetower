#include "card_registry.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "consts.h"
#include "common/ecs/component.h"
#include "common/resources/resource_manager.h"
#include "common/resources/texture.h"
#include "core/components/card_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"

namespace core {

    using common::ecs::Component;
    using common::resources::ResourceManager;
    using common::resources::Texture;
    using core::components::CardComponent;
    using core::components::PositionComponent;
    using core::components::SizeComponent;

    CardRegistry::CardRegistry() {
        this->initRegistry();
    }

    CardRegistry::CardPrototype CardRegistry::getCardPrototype(int card_id) {
        if (this->card_prototypes.count(card_id)) {
            std::vector<std::unique_ptr<Component>> clonedComponents;
            for (const auto& component : this->card_prototypes.at(card_id)) {
                clonedComponents.push_back(component->clone());
            }
            return clonedComponents;
        }
        else {
            std::cout << "Card prototype not found for id: " << card_id << "\n";
            return {};
        }
    }

    // Private functions

    void CardRegistry::initRegistry() {
        this->addCard(11, "Aqua Elemental", "011_aqua_elemental.png");
    }

    void CardRegistry::addCard(int card_id, std::string card_name, std::string card_art_name) {
        std::unique_ptr<CardComponent> card_component = std::make_unique<CardComponent>(
            ResourceManager::LoadTexture(
                ("assets/cards/art/" + card_art_name).c_str(), card_name, /*alpha=*/ true),
            card_name
        );
        this->card_prototypes[card_id].push_back(std::move(card_component));
        this->card_prototypes[card_id].push_back(std::make_unique<SizeComponent>(core::CARD_DEFAULT_WIDTH, core::CARD_DEFAULT_HEIGHT));
        this->card_prototypes[card_id].push_back(std::make_unique<PositionComponent>(glm::vec2(0.0f)));
    }

} // namespace core