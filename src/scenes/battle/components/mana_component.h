#ifndef MANA_COMPONENT_H
#define MANA_COMPONENT_H

#include <memory>

#include "common/ecs/component.h"

namespace scenes {
namespace battle {
namespace components {

/*
 * Indicates the current and max mana a 'player' has.
 */
class ManaComponent : public common::ecs::Component {
 public:
  ManaComponent(int max_mana) : current_mana(0), max_mana(max_mana) {}

  std::unique_ptr<Component> clone() const override {
    return std::make_unique<ManaComponent>(max_mana);
  }

  int getComponentIdInstance() const override {
    return Component::getComponentId<ManaComponent>();
  }

  int getCurrentMana() const { return this->current_mana; }

  void setCurrentMana(int current_mana) { this->current_mana = current_mana; }

  int getMaxMana() const { return this->max_mana; }

  void setMaxMana(int max_mana) { this->max_mana = max_mana; }

 private:
  int current_mana, max_mana;
};
}  // namespace components
}  // namespace battle
}  // namespace scenes

#endif  // MANA_COMPONENT_H