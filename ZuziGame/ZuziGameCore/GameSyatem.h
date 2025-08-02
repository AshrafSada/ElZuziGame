#pragma once
#include "GameEntity.h"
#include <array>
#include <vector>

struct GameSystem
{
public:
    GameSystem( )
    {
        // initialized to index 0 (1 player)
        m_playerIndex = 0; // TODO: change when using maps
    }

public:
    static const size_t LAYER_IDX_LEVEL = 0;
    static const size_t LAYER_IDX_CHARACTERS = 1;

public:
    std::array<std::vector<GameEntity>, 2> m_gameLayers;
    int m_playerIndex;
};
