#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <vector>

#include "common/2D/renderer_manager.h"
#include "entity.h"
#include "render_system.h"
#include "system.h"

namespace common {
    namespace ecs {

        /* Manager of the ecs system, handles the coordination of the different parts. */
        class Engine {
        public:
            using EntityList = std::vector<std::unique_ptr<Entity>>;
            using SystemsList = std::vector<std::unique_ptr<System>>;
            using RenderSystemsList = std::vector<std::unique_ptr<RenderSystem>>;

            Engine() = default;
            ~Engine() = default;

            const EntityList& getEntities() const {
                return this->entities;
            }

            Entity& newEntity();

            /*
            * Registers a given system with the given arguments.
            */
            template<typename T, typename... Args>
            void registerSystem(Args&&... args) {
                std::unique_ptr<T> system = std::make_unique<T>(std::forward<Args>(args)...);
                this->systems.push_back(std::move(system));
            }

            /*
            * Registers a given render system with the given arguments.
            */
            template<typename T, typename... Args>
            void registerRenderSystem(Args&&... args) {
                std::unique_ptr<T> system = std::make_unique<T>(std::forward<Args>(args)...);
                this->render_systems.push_back(std::move(system));
            }

            void runSystems() {
                for (const auto& system : this->systems) {
                    system->process(*this);
                }
            }

            void runRenderSystems(std::shared_ptr<common::twod::RendererManager> renderer_manager) {
                for (const auto& system : this->render_systems) {
                    system->render(*this, renderer_manager);
                }
            }

        private:
            static int number_of_entities;

            EntityList entities;
            SystemsList systems;
            RenderSystemsList render_systems;
        };

    } // namespace ecs
} // namespace common

#endif // ENGINE_H