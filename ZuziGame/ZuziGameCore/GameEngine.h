#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameEntity.h"
#include "GameResources.h"
#include "GameSDLState.hpp"
#include "GameState.hpp"

class GameEngine
{
public:
    GameEngine( ) = default;
public:
    // Initialize SDL
    bool InitializeSDL( );

    // create SDL window
    SDL_Window *CreateSDLWindow( int width, int height, SDL_WindowFlags winFlags );

    // create SDL renderer
    SDL_Renderer *CreateSDLRenderer( SDL_Window *sdlWin, const char *driverName, int logicalWidth, int logicalHeight );

    // clean and destroy SDL renderer and window
    void CleanUp( GameSDLState &sdlState );

    // draw game entity or sprite
    void DrawGameEntity( GameSDLState &sdlState, GameState &gameState, GameEntity &entityObject, Uint64 deltaTime );

    /// <summary>
    /// Update game entity
    /// </summary>
    /// <param name="gResources">: Game Resources</param>
    /// <param name="sdlState">: Game SDL State</param>
    /// <param name="gameState">: Game State</param>
    /// <param name="entityObject">: Game Entity Object To Update</param>
    /// <param name="deltaTime">: Change in Ticks since window loop started</param>
    void UpdateGameEntity( GameResources &gResources, GameSDLState &sdlState, GameState &gameState, GameEntity &entityObject, Uint64 deltaTime );
};
