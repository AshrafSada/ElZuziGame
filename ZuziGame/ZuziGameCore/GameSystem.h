#pragma once

#include <array>
#include <vector>
#include "GameEntity.h"

class GameSystem
{
public:
    GameSystem( );

public:
    static const size_t LAYER_IDX_LEVEL = 0;
    static const size_t LAYER_IDX_CHARACTERS = 1;

public:
    // game players array initialized to 2 game entities
    std::array<std::vector<GameEntity>, 2> m_gameEntityLayers;
    // player index initialize to 0 for player 1 in constructor
    int m_playerIndex;
};
