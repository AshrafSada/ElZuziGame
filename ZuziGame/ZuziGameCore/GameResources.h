#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <vector>
#include "GameAnimation.h"
#include "GameSDLState.hpp"

class GameResources
{
public:
    GameResources( );
    // player idle index
    const int ANIM_PLAYER_IDLE = 0;
public:
    /// <summary>
    /// Load Resources
    /// </summary>
    /// <param name="state"></param>
    void loadResources( GameSDLState &state );

    /// <summary>
    /// Destroy textures unload resources
    /// </summary>
    void unLoadResources( );

    /// <summary>
    /// Load texture from file
    /// </summary>
    /// <param name="state:">Game SDL State</param>
    /// <param name="filePath:">Texture file path</param>
    /// <returns>SDL Texture *</returns>
    SDL_Texture *loadTexture( GameSDLState &state, const std::string &filePath );
public:
    // player game animation vector
    std::vector<GameAnimation> m_playerAnimations;
    // SDL Textures vector
    std::vector<SDL_Texture *> m_textures;
};
