#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "GameAnimation.h"
#include "GameEnumerations.hpp"
#include "SDL3/SDL.h"

struct PlayerEntity
{
public:
    PlayerState m_playerState;
    GameTimer m_weaponTimer;
    PlayerEntity( ) : m_weaponTimer( 0.1f )
    {
        m_playerState = PlayerState::Idle;
    }
};

struct EnemyEntity
{
    EnemyState m_enemyState;
    GameTimer m_enemyDamageTimer;
    int m_healthPoints;

    EnemyEntity( )
        :
        m_enemyState( EnemyState::Shuffling ),
        m_enemyDamageTimer( 0.5f )
    {
        m_healthPoints = 100; // default enemy health points
    }
};

struct BulletEntity
{
    BulletState m_bulletState;
    BulletEntity( ) : m_bulletState( BulletState::Moving )
    { }
};

struct LevelEntity
{ };

union EntityUnion
{
    PlayerEntity um_player;
    LevelEntity um_level;
    EnemyEntity um_enemy;
    BulletEntity um_bullet;
};

class GameEntity
{
public:
    /// <summary>
    /// Game Entity Constructor Initialization List (CIL)
    /// <remarks>
    /// CIL is required for/when const, reference type, zero constructor members
    /// <remarks>
    /// </summary>
    GameEntity( );

public:
    // Entity union
    EntityUnion u_entityUnion;
    // flash timer
    GameTimer m_flashTimer;
    // collider Rect
    SDL_FRect m_collider;
public:
    // entity type
    GameEntityType m_entityType;
    // SDL texture to use by Draw function
    SDL_Texture *m_textureToDraw{ };
    // game animations vector
    std::vector<GameAnimation> m_animations;
    // entity position, velocity, acceleration GLM VEC2
    glm::vec2  m_acceleration, m_position, m_velocity;
public:
    // entity direction on X axis, -1=left, 1=right
    float m_direction;
    // max speed on X axis
    float m_maxSpeedX;
    // current animation index
    int m_currentAnimation;
    // sprite frame
    int m_spriteFrame;
    // dynamic
    bool m_Dynamic;
    // grounded
    bool m_grounded;
    // should flash
    bool m_flash;
};
