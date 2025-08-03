#include "GameResources.h"

GameResources::GameResources( )
{ }

SDL_Texture *GameResources::loadTextureFromFile( SDL_Renderer *renderer, const std::string &filePath )
{
    SDL_Texture *tex = IMG_LoadTexture( renderer, filePath.c_str( ) );
    textures.push_back( tex );
    return tex;
}

void GameResources::loadResources( SDL_Renderer *renderer )
{
    playerAnimations.resize( 5 );
    playerAnimations[ANIM_PLAYER_IDLE] = GameAnimation( 8, 2.2f );
    idleTex = loadTextureFromFile( renderer, ".\\.\\GameAssets\\idle.png" );
}

void GameResources::unLoadResources( )
{
    for (SDL_Texture *tex : textures)
    {
        SDL_DestroyTexture( tex );
    }
}
