#pragma once

enum GameEntityType
{
    Player,
    Level,
    Enemy,
};

enum PlayerState
{
    Idle,
    Running,
    Jumping
};

enum BulletState
{
    Moving,
    colliding,
    Inactive
};

enum EnemyState
{
    Shuffling,
    Damaged,
    Dead
};
