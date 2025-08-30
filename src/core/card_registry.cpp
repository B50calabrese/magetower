#include "card_registry.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "common/ecs/component.h"
#include "common/resources/resource_manager.h"
#include "common/resources/texture.h"
#include "core/card_loader_xml.h"
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

CardRegistry::CardRegistry() { this->initRegistry(); }

CardRegistry::CardPrototype CardRegistry::getCardPrototype(int card_id) {
  if (this->card_prototypes.count(card_id)) {
    std::vector<std::unique_ptr<Component>> clonedComponents;
    for (const auto& component : this->card_prototypes.at(card_id)) {
      clonedComponents.push_back(component->clone());
    }
    return clonedComponents;
  } else {
    std::cout << "Card prototype not found for id: " << card_id << "\n";
    return {};
  }
}

std::vector<int> CardRegistry::getAllCardIds() const {
  std::vector<int> card_ids;
  for (const auto& pair : this->card_prototypes) {
    card_ids.push_back(pair.first);
  }
  return card_ids;
}

void CardRegistry::addCard(
    int card_id,
    std::vector<std::shared_ptr<common::ecs::Component>> components) {
  for (auto component : components) {
    this->card_prototypes[card_id].push_back(component->clone());
  }
}

// Private functions

void CardRegistry::initRegistry() {
  CardLoaderXML card_loader_xml;
  const std::string file_path = "assets/cards/card_registry.xml";
  card_loader_xml.loadCards(file_path, *this);
}

}  // namespace core