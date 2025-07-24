# EL Zuzi Game

Simple 2D game developed using C++, and SFML framework.

## Solution Architecture

Using Entity-Component-System (ECS) programming paradigm.
The naming convention of components must start with capital `C`, indicating that the object is a component.
Using smart pointers in C++ for better memory management, side-by-side with Resource Acquisition Is Initialization (RAII) programming technique, to tie the lifetime of a resource to the lifetime of an object.

The following diagram illustrates the ECS implementation workflow in the solution.

![ECS](../ELZuziGame/Diagrams/ECS_Diagram.drawio.png)

## Development Guidelines

Data should be separated from the logic code, to make sure that changing either will not affect the other.

The **Entity Manager** uses the factory design pattern, to handle the creation and lifetime of all objects.

For example in addition to the factory design pattern to be implemented, the entity manager may have functions that handle:

- `addEntity`
- `removeEntity`
- `storage`
- `bookKeeping`

Also, the implemented factory should make sure that the user cannot create its own entities.

**Entity Tags** we may want to group entities by some common factor, say functionality, in this case we need tags, that are of type string, or of type enum (integer) that can group our entities.

All entities will be stored in a vector of type shared pointer, as smart pointer for safer memory management.

For example of Entity Manager:

```c++
 // stores the entities
 typedef std::vector<std::shared_ptr<Entity>> EntityVector;
 // store the tags
 typedef std::map<std::string, EntityVector> EntityMap;

 class EntityManager {
    EntityVector m_entityVector;
    EntityMap m_entityMap;
    size_t m_totalEntities = 0;
public:
    EntityManager();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    EntityVector& getEntities();
    EntityVector& getEntities(const std::string& tag);
 }
```

**Iteration Invalidation** is caused by modifying the contents of a collation at the same time we are iterating through it.

Iteration invalidation happens almost always in games, while iterating through a vector array, vector functions, may cause memory reallocation by:

- Adding to vector using push_back, or insert functions.
- Resizing vector array by recreating internal array.
- Erasing element from vector array using erase, or pop_back functions.

Example of Iteration Invalidation:

```c++
void sCollision(){
    EntityVector bullets;
    EntityVector tiles;
    for (auto &b: bullets){
        for (auto &t: tiles){
            if(Physics::IsCollision(b,t))
            {
                bullets.erase(b);
            }
        }
    }
}
```

The base rule to avoid **Iteration Invalidation** is never modify an array during iteration.

**Delayed Effects** as an effective solution to **Iteration Invalidation**, by delaying the actions modifying the collections until it is safe to do so, and that can be achieved by adding a function to **Entity Manager** to update by requesting an update then executing it when it is safe.

Example of **Delayed Effects** entity manager with update function:

```c++
 // stores the entities
 typedef std::vector<std::shared_ptr<Entity>> EntityVector;
 // store the tags
 typedef std::map<std::string, EntityVector> EntityMap;

 class EntityManager {
    EntityVector m_entityVector;
    // entity to update container
    EntityVector m_entityToUpdate;
    EntityMap m_entityMap;
    size_t m_totalEntities = 0;
public:
    EntityManager();
    // update function
    void updateEntity();
    std::shared_ptr<Entity> addEntity(const std::string& tag);
    EntityVector& getEntities();
    EntityVector& getEntities(const std::string& tag);
 }
```

### Math for 2D Graphics

Linear algebra is used to calculate required results for handling 2D, and 3D graphics in game design and development.

In leaner algebra the Euclidean Geometry is used as a axiomatic system, to help achieve the following key features:

- Based on five postulates (axioms).
- Describes geometry of flat (2D and 3D) spaces.
- Used in classical mathematical constructions with compass and ruler.

For any graphics developer, especially game developers, the Euclidean Geometry, must be understood, to be able to fathom and handle the mathematical concepts, which will help you build better games.

What are the 5 Axioms of Euclidean Geometry:

1. A straight line can be drawn from any point to any other point.
2. A straight line segment can be extended indefinitely.
3. A circle can be drawn with center and radius.
4. All right angles are equal.
5. If a line intersects two others, and the interior angles on one side sum to less than two right angles, those two lines will meet on that side, this is called (Parallel Postulate).

The Euclidean Geometry, is based on X coordinate, and Y coordinate.

So any point represented must have (x, y) coordinates, for example a = (7,3).

![Math for 2D games](./Diagrams/Math_for_2D_Games.png)

## Game Engine and Game Classes

Despite the fact that this game is very small, compared to other games, nevertheless we are building it in a professional enterprise level, to be as a standard example of 2D game development.

The Class diagram that illustrates the various classes and objects of the game engine, is intended to illustrate to the developers what is it that we need to build exactly.

Our class diagram is the base of the game architecture and can be extended in the future.

The naming convections of classes and methods in the game engine, based on previously described ECS paradigm:

- Private member's name start with m.
- System function's name start with s.
- Component's name starts with c.

Note: private members are preceded by minus sign, public members preceded by plus sign.

```mermaid
---
title: 'Game Engine Class Diagram 1'
config:
    theme: "dark"
---
classDiagram
    direction L
    class Vec2 {
        + x: double
        + y: double
        + operator() ==: bool
        + operator() !=: bool
        + operator() +: Vec2
        + operator() -: Vec2
        + operator() *: Vec2
        + operator() /: Vec2
        + normalize(): void
        + length(): double
    }
    class CCollision {
        + radius: float
    }
    class CScore {
        + score: int
    }
    class CTransform {
        + pos: vec2
        + speed: Vec2
        + scale: Vec2
        + angle: Vec2
    }

```

```mermaid
---
title: 'Game Engine Class Diagram 2'
config:
    theme: "dark"
---
classDiagram
    direction L
        class Entity {
            - m_tag: string
            - m_active: bool
            - m_id:size_t
            + cTransform: CTransform
            + cShape: CShape **
            + cCollision: CCollision **
            + cInput: CInput
            + cScore: CScore
            + cLifespan: CLifespan
            + detroy(): void
            + isActive(): bool
            + tag(): string &
            + id(): size_t
        }
        class EntityManager {
            - m_entities: vector<Entity>
            - m_entityMap: map<string, Entity>
            - m_entityToAdd: vector<Ebntity>
            - init(): void
            + update(): void
            + addEntity(args): shared_ptr<Entity>
            + getEntities(): vector<shared_ptr<Entity>> &
            + getEntities(args): vector<shared_ptr<Entity>> &
        }
        class Game {
            - m_window: sf::RenderWindow
            - m_entities: EntityManager
            - m_player: Entity
            - m_paused: bool
            - m_running: bool
            - init(): void
            + update(): void
            - sMovement(): void
            - sUserInput(): void
            - sRender(): void
            - sEnemySpawner(): void
            - sCollision(): void
        }

```
