#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <vector>
#include "GameAnimation.h"

class GameResources
{
public:
    GameResources( );

public:
    SDL_Texture *loadTextureFromFile( SDL_Renderer *renderer, const std::string &filePath );
    void loadResources( SDL_Renderer *renderer );
    void unLoadResources( );

public:
    const int ANIM_PLAYER_IDLE = 0;
    std::vector<GameAnimation> playerAnimations;
    std::vector<SDL_Texture *> textures;
    SDL_Texture *idleTex{ };
};
