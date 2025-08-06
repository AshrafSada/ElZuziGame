#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "GameAnimation.h"
#include "SDL3/SDL.h"

enum GameEntityType
{
    player = 0,
    level = 1,
    enemy = 2
};

class GameEntity
{
public:
    GameEntity( );

public:
    // entity position, velocity, acceleration GLM VEC2
    glm::vec2 m_position, m_velocity, m_acceleration;
    // entity type
    GameEntityType m_entityType;
    // entity direction on X axis, -1=left, 1=right
    float m_direction;
    // game animations vector
    std::vector<GameAnimation> m_animations;
    // current animation index
    int m_currentAnimation;
    // SDL texture to use by Draw function
    SDL_Texture *m_textureToDraw{ };
};
