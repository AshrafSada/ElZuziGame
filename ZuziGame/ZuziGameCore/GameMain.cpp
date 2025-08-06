#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameEntity.h"
#include "GameResources.h"
#include "GameSDLState.hpp"
#include "GameState.hpp"

// function declarations
static bool InitializeSDL( );
static SDL_Window *CreateSDLWindow( int width, int height, SDL_WindowFlags winFlags );
static SDL_Renderer *CreateSDLRenderer( SDL_Window *sdlWin, const char *driverName, int logicalWidth, int logicalHeight );
static void CleanUp( GameSDLState &sdlState );
static void DrawGameEntity( GameSDLState &sdlState, GameState &gameState, GameEntity &entityObject, float deltaTime );

static void getHardwareInfo( );

// NOTE: required by SDL  argc: argument count, argv: argument value
int main( int argc, char *argv[] )
{
    // IMPORTANT: get hardware info, don't NOT used in production
    getHardwareInfo( );

    // SDL initialization
    InitializeSDL( );

    // instance of Game SDL State
    GameSDLState sdlState{
        .winWidth = 1024,
        .winHeight = 780,
        .logWidth = 960,
        .logHeight = 480,
        .clrRed = 33,
        .clrGreen = 44,
        .clrBlue = 66,
        .clrAlpha = 255
    };
    // create SDL window
    sdlState.window = CreateSDLWindow( sdlState.winWidth, sdlState.winHeight, SDL_WINDOW_RESIZABLE );

    // create SDL renderer
    sdlState.renderer = CreateSDLRenderer( sdlState.window, NULL, sdlState.logWidth, sdlState.logHeight );

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
    player.m_entityType = GameEntityType::player;
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
                CleanUp( sdlState );
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
                DrawGameEntity( sdlState, gState, entity, deltaTicks );
            }
        }

        // SDL built-in swap-chain will (flip) back buffer to the front buffer
        // and present renderer with updated changes
        SDL_RenderPresent( sdlState.renderer );
    }

    gRes.unLoadResources( );
    CleanUp( sdlState );
    return 0;
}

// implement in order of allocation (FIFO)

static bool InitializeSDL( )
{
    std::cout << "Game running ..." << std::endl;
    bool isSDLInitialized = SDL_Init( SDL_INIT_VIDEO );

    // Initialize SDL with init video flag
    if (!isSDLInitialized)
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,
            "SDL init error",
            "SDL initialization failed!", nullptr );
    }
    return isSDLInitialized;
}

// create SDL window and returns pointer to created window
static SDL_Window *CreateSDLWindow( int width, int height, SDL_WindowFlags winFlags )
{
    SDL_Window *sWin = SDL_CreateWindow( "ZUZI Game | Main Window", width, height, winFlags );
    if (!sWin)
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,
            "SDL window error",
            "SDL window creation failed!", sWin );
    }
    return sWin;
}

// create SDL renderer and return pointer to created renderer
static SDL_Renderer *CreateSDLRenderer( SDL_Window *sdlWin, const char *driverName, int logicalWidth, int logicalHeight )
{
    // create SDL Renderer (renderer driver name = NULL, let SDL find the best one to use)
    SDL_Renderer *sRenderer = SDL_CreateRenderer( sdlWin, driverName );
    if (!sRenderer)
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,
            "SDL renderer error",
            "SDL renderer creation failed!", sdlWin );
    }

    // set logical renderer presentation letter box to scale objects per window current size
    SDL_SetRenderLogicalPresentation( sRenderer, logicalWidth, logicalHeight,
        SDL_RendererLogicalPresentation::SDL_LOGICAL_PRESENTATION_LETTERBOX );

    return sRenderer;
}

// clean memory and destroy resource
static void CleanUp( GameSDLState &sdlState )
{
    SDL_DestroyRenderer( sdlState.renderer );
    SDL_DestroyWindow( sdlState.window );
}

// Draw game entity object
static void DrawGameEntity( GameSDLState &sdlState, GameState &gameState, GameEntity &entityObject, float deltaTime )
{
    // default sprite size
    const float spriteSize = 32.f;

    // setting src X based on current animation and sprite size
    float srcX = entityObject.m_currentAnimation != -1
        ? ((float)entityObject.m_animations[entityObject.m_currentAnimation].getCurrentFrameCount( ) * spriteSize)
        : 0.f;

    // FRect src and dst
    SDL_FRect srcRect{ srcX, 0, spriteSize, spriteSize };
    SDL_FRect dstRect{ entityObject.m_position.x, entityObject.m_position.y, spriteSize, spriteSize };

    // flip mode ternary operator
    SDL_FlipMode flipMode = entityObject.m_direction == -1
        ? SDL_FLIP_HORIZONTAL
        : SDL_FLIP_NONE;

    // render texture rotated
    SDL_RenderTextureRotated( sdlState.renderer, entityObject.m_textureToDraw, &srcRect, &dstRect, 0, NULL, flipMode );
}

// technical hardware info query
static void getHardwareInfo( )
{
    // get number of audio drivers
    int audioDrivers = SDL_GetNumAudioDrivers( );
    std::cout << "Audio drivers: " << audioDrivers << std::endl;

    for (int i = 0; i < audioDrivers; i++)
    {
        std::cout << "Audio driver " << i + 1 << " Name: " << SDL_GetAudioDriver( i ) << std::endl;
    }

    // get number of GPU drivers
    int videoDrivers = SDL_GetNumGPUDrivers( );
    std::cout << "Video GPU drivers: " << videoDrivers << std::endl;

    for (int i = 0; i < videoDrivers; i++)
    {
        std::cout << "Video driver " << i + 1 << " Name: " << SDL_GetVideoDriver( i ) << std::endl;
    }

    // get system RAM size
    auto sysRAM = SDL_GetSystemRAM( );
    std::cout << "System RAM size: " << sysRAM << "MB" << std::endl;
}
