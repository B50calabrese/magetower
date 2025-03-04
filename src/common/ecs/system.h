#ifndef SYSTEM_H
#define SYSTEM_H

namespace common {
    namespace ecs {

        class Engine;

        /* Base class for systems that act on components. */
        class System {
        public:
            virtual ~System() = default;

            // This is the main function that systems need to override to implement 'logic'.
            virtual void process(Engine& engine) = 0;
        };

    } // namespace ecs
} // namespace common

#endif // SYSTEM_H