#pragma once

#include "GameAnimation.h"
#include <glm/glm.hpp>
#include <SDL3/SDL.h>

struct GameEntity
{
public:
    enum EntityType
    {
        player, level, enemy
    };

public:
    GameEntity( )
    {
        m_entityType = EntityType::level;
        m_direction = 1; // 1 right -1 left
        m_position = m_velocity = m_acceleration = glm::vec2( 0 );
        m_currentAnimation = -1; // -1 no animation
        m_texture = nullptr; // nullPtr no texture
    }

public:
    EntityType m_entityType;
    glm::vec2 m_position, m_velocity, m_acceleration;
    float m_direction;
    std::vector<GameAnimation> m_animations;
    int m_currentAnimation;
    SDL_Texture *m_texture;
};
