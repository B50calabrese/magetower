#ifndef MAGETOWER_SRC_CORE_CARD_REGISTRY_H_
#define MAGETOWER_SRC_CORE_CARD_REGISTRY_H_

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "common/ecs/component.h"

namespace core {

// Container class that contains references to all the cards possible in the
// game. Makes it easier to create cards on the fly for construction of the
// deck/rendering.
class CardRegistry {
 public:
  using CardPrototype = std::vector<std::unique_ptr<common::ecs::Component>>;

  CardRegistry();

  CardPrototype GetCardPrototype(int card_id);

  void AddCard(int card_id,
               std::vector<std::shared_ptr<common::ecs::Component>> components);

 private:
  std::map<int, CardPrototype> card_prototypes_;

  void InitRegistry();

  void AddCard(int card_id, std::string card_name, std::string card_art_name);
};

}  // namespace core

#endif  // MAGETOWER_SRC_CORE_CARD_REGISTRY_H_