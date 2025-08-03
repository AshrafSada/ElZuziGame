#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <SDL3/SDL.h>
#include "GameAnimation.h"

class GameEntity
{
public:
    enum EntityType
    {
        player, level, enemy
    };
public:
    GameEntity( );

public:
    // entity type initialized to level in constructor
    EntityType m_entityType;
    // vec2 type coordinates
    glm::vec2 m_position, m_velocity, m_acceleration;
    // -1 left 1 right on x axis
    float m_direction;
    // auto initialized here
    std::vector<GameAnimation> m_animations;
    // initialize to -1 for no animation in constructor
    int m_currentAnimation;
    // initialize to nullptr in constructor
    SDL_Texture *m_texture;
};
