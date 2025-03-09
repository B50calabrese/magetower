#ifndef COMPONENT_H
#define COMPONENT_H

namespace common {
    namespace ecs {

        /* Base class for all components. */
        class Component {
        public:
            virtual ~Component() = default;

            /*
            * Gets the unique component id for a given component.
            */
            template<typename T>
            static int getComponentId() {
                static int component_id = Component::next_component_id++;
                return component_id;
            }
        
        private:
            static int next_component_id;
        };

    } // namespace ecs
} // namespace common

#endif // COMPONENT_H