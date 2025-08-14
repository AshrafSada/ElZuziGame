#include "GameResources.h"

GameResources::GameResources( )
    :
    m_playerAnimations( ),
    m_textures( )
{ }

void GameResources::loadResources( GameSDLState &state )
{
    // resize vector to use indices
    m_playerAnimations.resize( 2 );
    // index player animation and add to it new animation
    GameAnimation gAnimation( 8, 1.6f );
    m_playerAnimations[ANIM_PLAYER_IDLE] = gAnimation;
}

void GameResources::unLoadResources( )
{
    for (auto *tex : m_textures)
    {
        SDL_DestroyTexture( tex );
    }
}

SDL_Texture *GameResources::loadTexture( GameSDLState &state, const std::string &filePath )
{
    // loading texture from sprite file
    SDL_Texture *tex = IMG_LoadTexture( state.renderer, filePath.c_str( ) );

    // nearest neighbor scaling to avoid blur
    SDL_SetTextureScaleMode( tex, SDL_SCALEMODE_NEAREST );

    // check texture loaded
    if (!tex)
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR, "Texture render error", "An error occurred while loading texture", state.window );
        return nullptr;
    }

    // adding texture to textures vector
    m_textures.push_back( tex );

    // return texture
    return tex;
}
