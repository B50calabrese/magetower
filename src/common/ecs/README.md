# Entity-Component-System (ECS)

This package provides basic functionality for an 'ecs' system in the game engine. Note that it isn't explicitly
forced by framework intentionally, to allow for flexibility.

## Definitions

* Entity - Contains a set of components. Usually defines game objects in the world.
* Component - Contains data about a given entity, and indicates a particular 'aspect' that an entity may have.
* System - Runs the business logic acting on a set of entities with a given component.
  * RenderSystem - A subset of systems intended to be used by the renderer.
* Engine - Manages the various systems, entities, and components defined by the user.