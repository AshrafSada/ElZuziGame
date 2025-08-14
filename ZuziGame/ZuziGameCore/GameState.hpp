#pragma once

#include <array>
#include <vector>
#include "GameEntity.h"
#include "GameSDLState.hpp"

struct GameState
{
public:
    GameState( const GameSDLState &sdlState )
    {
        m_playerIndex = -1;
    }

public:
    // indices of level layer
    static const size_t LAYER_IDX_LEVEL = 0;
    // indices of characters layer
    static const size_t LAYER_IDX_CHARACTERS = 1;

public:
    // layers array of vector game entity and size 2
    std::array<std::vector<GameEntity>, 2> m_gameEntityLayers;
    // player (game entity) index
    int m_playerIndex;
};
