#ifndef CARD_LOADER_XML_H
#define CARD_LOADER_XML_H

#include <memory>
#include <string>

#include "common/ecs/component.h"
#include "tinyxml2.h"

namespace core {

// Forward declaration of the CardRegistry class.
class CardRegistry;

class CardLoaderXML {
 public:
  /**
   * Loads cards from the given XML file and populates the CardRegistry with the
   * definitions.
   * @param file_path the path of the XML file
   * @param registry the CardRegistry instance to register the cards with.
   * @return true if loading was successful
   */
  bool loadCards(const std::string& file_path, CardRegistry& card_registry);

 private:
  std::shared_ptr<common::ecs::Component> parseComponent(
      tinyxml2::XMLElement* component_element);
};

}  // namespace core

#endif  // CARD_LOADER_XML_H