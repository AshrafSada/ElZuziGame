#pragma once

#include "GameAnimation.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <vector>

struct GameResources
{
public:
    const int ANIM_PLAYER_IDLE = 0;
    std::vector<GameAnimation> playerAnimations;
    std::vector<SDL_Texture *> textures;
    SDL_Texture *idleTex{ };

    // loading game assets using SDL Image Texture from file path
    SDL_Texture *loadTextureFromFile( SDL_Renderer *renderer, const std::string &filePath )
    {
        SDL_Texture *tex = IMG_LoadTexture( renderer, filePath.c_str( ) );
        textures.push_back( tex );
        return tex;
    }

    void loadResources( SDL_Renderer *renderer )
    {
        playerAnimations.resize( 5 );
        playerAnimations[ANIM_PLAYER_IDLE] = GameAnimation( 8, 1.6f );
        idleTex = loadTextureFromFile( renderer, ".\\.\\GameAssets\\idle.png" );
    }

    void unLoadResources( )
    {
        for (SDL_Texture *tex : textures)
        {
            SDL_DestroyTexture( tex );
        }
    }
};
