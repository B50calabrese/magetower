#include "core/card_loader_xml.h"

#include <memory>
#include <string>
#include <vector>

#include "common/ecs/component.h"
#include "common/resources/resource_manager.h"
#include "common/utils/logger.h"
#include "core/card_registry.h"
#include "core/components/card_component.h"
#include "core/components/position_component.h"
#include "core/components/size_component.h"
#include "core/consts.h"
#include "tinyxml2.h"

namespace core {

using common::ecs::Component;
using core::components::CardComponent;
using core::components::PositionComponent;
using core::components::SizeComponent;

bool CardLoaderXML::LoadCards(const std::string& file_path,
                              CardRegistry& card_registry) {
  tinyxml2::XMLDocument doc;

  if (doc.LoadFile(file_path.c_str()) != tinyxml2::XML_SUCCESS) {
    common::utils::Logger::Error(
        "XML Loader Error: Could not load card file: " + file_path + "\n");
    return false;
  }

  tinyxml2::XMLElement* root = doc.RootElement();
  if (!root || (std::string(root->Name()) != "Cards")) {
    common::utils::Logger::Error(
        "XML Loader Error: Root element must be <Cards>\n");
    return false;
  }

  for (tinyxml2::XMLElement* card_element = root->FirstChildElement("Card");
       card_element != nullptr;
       card_element = card_element->NextSiblingElement("Card")) {
    const char* id = card_element->Attribute("Id");
    if (!id) {
      common::utils::Logger::Error(
          "XML Loader Error: Card without id attribute\n");
      return false;
    }
    std::string id_string = id;
    common::utils::Logger::Info("XML Loader: Loading card id: " + id_string);

    std::vector<std::shared_ptr<Component>> components;
    for (tinyxml2::XMLElement* component_element =
             card_element->FirstChildElement("Component");
         component_element != nullptr;
         component_element =
             component_element->NextSiblingElement("Component")) {
      auto component = ParseComponent(component_element);
      if (component) {
        components.push_back(component);
      }
    }

    // Each card has the following components by default.
    components.push_back(std::make_shared<SizeComponent>(
        core::CARD_DEFAULT_WIDTH, core::CARD_DEFAULT_HEIGHT));
    components.push_back(std::make_shared<PositionComponent>(glm::vec2(0.0f)));

    common::utils::Logger::Info(
        "XML Loader: Registering card id: " + id_string + "\n");
    card_registry.AddCard(std::stoi(id_string), components);
  }
  return true;
}

// Private functions

std::shared_ptr<Component> CardLoaderXML::ParseComponent(
    tinyxml2::XMLElement* component_element) {
  if (!component_element) {
    return nullptr;
  }
  const char* type = component_element->Attribute("type");
  if (!type) {
    common::utils::Logger::Error("XML Loader Error: Component without type\n");
    return nullptr;
  }

  std::string type_string = type;

  if (type_string == "CardComponent") {
    const char* name = component_element->FirstChildElement("Name")->GetText();
    const char* card_art =
        component_element->FirstChildElement("CardArt")->GetText();
    if (!name || !card_art) {
      common::utils::Logger::Error(
          "XML Loader Error: CardComponent malformed\n");
      return nullptr;
    }
    std::string card_art_string = card_art;
    return std::make_shared<CardComponent>(
        common::resources::ResourceManager::LoadTexture(
            ("assets/cards/art/" + card_art_string).c_str(), name,
            /*alpha=*/true),
        name);
  }

  common::utils::Logger::Error("XML Loader Error: Unknown component type " +
                               type_string + "\n");
  return nullptr;
}

}  // namespace core