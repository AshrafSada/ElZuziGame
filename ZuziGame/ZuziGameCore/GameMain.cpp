#include "GameEngine.h"

// NOTE: required by SDL  argc: argument count, argv: argument value
int main( int argc, char *argv[] )
{
    // instance of Game Engine
    GameEngine gEngine{ };

    // SDL initialization
    if (!gEngine.InitializeSDL( ))
    {
        return -1;
    }

    // instance of Game SDL State
    GameSDLState sdlState{
        .winWidth = 1600,
        .winHeight = 900,
        .logWidth = 640,
        .logHeight = 320,
        .clrRed = 33,
        .clrGreen = 44,
        .clrBlue = 66,
        .clrAlpha = 255,
    };

    // create SDL window
    sdlState.window = gEngine.CreateSDLWindow( sdlState.winWidth, sdlState.winHeight, SDL_WINDOW_RESIZABLE );

    // create SDL renderer
    sdlState.renderer = gEngine.CreateSDLRenderer( sdlState.window, NULL, sdlState.logWidth, sdlState.logHeight );

    // instance of game resources
    GameResources gRes{ };
    // load game resources
    gRes.loadResources( sdlState );

    // create idle texture
    SDL_Texture *idleTex = gRes.loadTexture( sdlState, "GameAssets/idle.png" );

    // instance of game state
    GameState gState{ sdlState };

    // create player
    GameEntity player;
    player.m_entityType = GameEntityType::Player;
    player.m_textureToDraw = idleTex;
    player.m_animations = gRes.m_playerAnimations;
    player.m_currentAnimation = gRes.ANIM_PLAYER_IDLE;
    player.m_position = glm::vec2( 300, 150 );
    player.m_maxSpeedX = 100;
    gState.m_gameEntityLayers[gState.LAYER_IDX_CHARACTERS].push_back( player );

    // Game SDL State get key pressed
    sdlState.keysPressed = SDL_GetKeyboardState( nullptr );

    // set sprite movement (per second, not per frame)
    Uint64 startTicks = SDL_GetTicks( );

    // create window loop
    bool isGameRunning = true;
    while (isGameRunning)
    {
        // get current time ticks
        Uint64 currentTicks = SDL_GetTicks( );
        // get ticks delta in seconds
        Uint64 deltaTicks = (currentTicks - startTicks) / 1000;

        // handling window events
        SDL_Event event{ 0 };
        SDL_PollEvent( &event );
        switch (event.type)
        {
            // handle quit event
            case SDL_EVENT_QUIT:
            {
                isGameRunning = false;
                std::cout << "Resource clean up started ..." << std::endl;
                gEngine.CleanUp( sdlState );
                break;
            }
            // handle window resize event
            case SDL_EVENT_WINDOW_RESIZED:
            {
                // letter box logical presentation mode enables resizing sprites with ratio scale proportional to resized window size
                sdlState.winWidth = event.window.data1;
                sdlState.winHeight = event.window.data2;
                break;
            }
        }

        // update all entity objects
        for (auto layers : gState.m_gameEntityLayers)
        {
            for (GameEntity &entityObj : layers)
            {
                gEngine.UpdateGameEntity( gRes, sdlState, gState, entityObj, deltaTicks );

                if (entityObj.m_currentAnimation != -1)
                {
                    entityObj.m_animations[entityObj.m_currentAnimation].stepAnimation( deltaTicks );
                }
            }
        }

        // set the renderer (RGB_A) surface colors
        SDL_SetRenderDrawColor( sdlState.renderer, sdlState.clrRed, sdlState.clrGreen, sdlState.clrBlue, sdlState.clrAlpha );

        // clear the renderer to update with new buffer
        SDL_RenderClear( sdlState.renderer );

        // Draw all entity objects
        for (auto layers : gState.m_gameEntityLayers)
        {
            for (GameEntity &entityObj : layers)
            {
                gEngine.DrawGameEntity( sdlState, gState, entityObj, deltaTicks );
            }
        }

        // Present(display) updated renderer and Swap-Chain flip buffers
        SDL_RenderPresent( sdlState.renderer );
        startTicks = currentTicks;
    }

    // unload game resources
    gRes.unLoadResources( );

    // clean up memory
    gEngine.CleanUp( sdlState );

    // return 0 for success exit code
    return 0;
}
