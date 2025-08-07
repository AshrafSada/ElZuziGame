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
    GameEngine( );
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
    void DrawGameEntity( GameSDLState &sdlState, GameState &gameState, GameEntity &entityObject, float deltaTime );
    // update game entity or sprite
    void UpdateGameEntity( GameResources &gResources, GameSDLState &sdlState, GameState &gameState, GameEntity &entityObject, float deltaTime );
};
