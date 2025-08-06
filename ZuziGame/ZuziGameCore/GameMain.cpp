#include "GameEngine.h"

// NOTE: required by SDL  argc: argument count, argv: argument value
int main( int argc, char *argv[] )
{
    // instance of Game Engine
    GameEngine gEngine{ };

    // IMPORTANT: get hardware info, don't NOT used in production
    gEngine.getHardwareInfo( );

    // SDL initialization
    gEngine.InitializeSDL( );

    // instance of Game SDL State
    GameSDLState sdlState{
        .winWidth = 1024,
        .winHeight = 780,
        .logWidth = 960,
        .logHeight = 480,
        .clrRed = 33,
        .clrGreen = 44,
        .clrBlue = 66,
        .clrAlpha = 255,
        .keysPressed = SDL_GetKeyboardState( NULL )
    };
    // create SDL window
    sdlState.window = gEngine.CreateSDLWindow( sdlState.winWidth, sdlState.winHeight, SDL_WINDOW_RESIZABLE );

    // create SDL renderer
    sdlState.renderer = gEngine.CreateSDLRenderer( sdlState.window, NULL, sdlState.logWidth, sdlState.logHeight );

    // instance of game state
    GameState gState{ };
    // instance of game resources
    GameResources gRes{ };
    // load game resources
    gRes.loadResources( sdlState );

    // create idle texture
    SDL_Texture *idleTex = gRes.loadTexture( sdlState, "GameAssets/idle.png" );

    // create player
    GameEntity player{ };
    player.m_entityType = GameEntityType::Player;
    player.m_textureToDraw = idleTex;
    // assign a copy of animations to player
    player.m_animations = gRes.m_playerAnimations;
    player.m_currentAnimation = gRes.ANIM_PLAYER_IDLE;
    gState.m_gameEntityLayers[GameState::LAYER_IDX_CHARACTERS].push_back( player );

    // set sprite movement (per second, not per frame)
    const bool *keysPressed = SDL_GetKeyboardState( NULL );
    Uint64 startTicks = SDL_GetTicks( );

    // load idle texture

    // create window loop
    bool isGameRunning = true;
    while (isGameRunning)
    {
        // get current time ticks
        Uint64 currentTicks = SDL_GetTicks( );
        // get ticks delta in seconds
        float deltaTicks = ((float)currentTicks - (float)startTicks) / 1000.f;

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

        // update sprite animation
        for (auto layers : gState.m_gameEntityLayers)
        {
            for (GameEntity &entity : layers)
            {
                if (entity.m_currentAnimation != -1)
                {
                    entity.m_animations[entity.m_currentAnimation].stepAnimation( deltaTicks );
                }
            }
        }

        // using the renderer (RGB_A)
        SDL_SetRenderDrawColor( sdlState.renderer, sdlState.clrRed, sdlState.clrGreen, sdlState.clrBlue, sdlState.clrAlpha );
        // clear the renderer
        SDL_RenderClear( sdlState.renderer );

        // draw the sprite
        for (auto layers : gState.m_gameEntityLayers)
        {
            for (GameEntity &entity : layers)
            {
                gEngine.DrawGameEntity( sdlState, gState, entity, deltaTicks );
            }
        }

        // SDL built-in swap-chain will (flip) back buffer to the front buffer
        // and present renderer with updated changes
        SDL_RenderPresent( sdlState.renderer );
    }

    gRes.unLoadResources( );
    gEngine.CleanUp( sdlState );
    return 0;
}
