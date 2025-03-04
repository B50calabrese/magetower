#ifndef COMPONENT_H
#define COMPONENT_H

namespace common {
    namespace ecs {

        /* Base class for all components. */
        class Component {
        public:
            virtual ~Component() = default;
        };

    } // namespace ecs
} // namespace common

#endif // COMPONENT_H