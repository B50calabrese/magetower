#include "engine.h"

namespace common {
    namespace ecs {

        int Engine::number_of_entities = 0;

        Entity& Engine::newEntity() {
            std::unique_ptr<Entity> entity = std::make_unique<Entity>(number_of_entities);
            this->entities.push_back(std::move(entity));
            return *entities.back();
        }

    } // namespace ecs
} // namespace common