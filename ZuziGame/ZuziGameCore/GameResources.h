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
    // player idl index
    const int ANIM_PLAYER_IDLE = 0;

public:
    // load resources with SDL state
    void loadResources( GameSDLState state );
    void unLoadResources( );
    // load Texture from file, and return texture
    SDL_Texture *loadTexture( GameSDLState &state, const std::string &filePath );
public:
    // player game animation vector
    std::vector<GameAnimation> m_playerAnimations;
    // SDL Textures vector
    std::vector<SDL_Texture *> m_textures;
};
