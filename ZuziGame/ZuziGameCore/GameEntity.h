#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "GameAnimation.h"
#include "SDL3/SDL.h"

enum GameEntityType
{
    Player = 0,
    Level = 1,
    Enemy = 2
};

enum PlayerState
{
    Idle, Running, Jumping
};

struct LevelEntity
{ };

struct EnemyEntity
{ };

struct PlayerEntity
{
public:
    PlayerState m_playerState;
    PlayerEntity( )
    {
        m_playerState = PlayerState::Idle;
    }
};

union EntityUnion
{
    PlayerEntity um_player;
    LevelEntity um_level;
    EnemyEntity um_enemy;
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
    // Entity union
    EntityUnion u_entityUnion;
    // entity direction on X axis, -1=left, 1=right
    float m_direction;
    // game animations vector
    std::vector<GameAnimation> m_animations;
    // current animation index
    int m_currentAnimation;
    // SDL texture to use by Draw function
    SDL_Texture *m_textureToDraw{ };
};
