#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameEntity.h"
#include "GameResources.h"
#include "GameSystem.h"

// function declarations
static bool InitializeSDL( );
static SDL_Window *CreateSDLWindow( int width, int height, SDL_WindowFlags winFlags );
static SDL_Renderer *CreateSDLRenderer( SDL_Window *sdlWin, const char *driverName, int logicalWidth, int logicalHeight );
static void CleanUpResources( SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer );
static void DrawGameEntityObject( SDL_Renderer *sdlRenderer, GameSystem &gameSystem, GameEntity &gameEntityObj, float deltaTime );

// NOTE: required by SDL  argc: argument count, argv: argument value
int main( int argc, char *argv[] )
{
    InitializeSDL( );

    // win width
    int gameWinWidth = 1024;
    int gameWinHeight = 780;
    // surface color
    int clrRed = 30;
    int clrGreen = 60;
    int clrBlue = 56;
    int clrAlpha = 255;
    // renderer presentation surface
    int logWidth = 960, logHeight = 320;

    // create SDL window
    SDL_Window *sWin = CreateSDLWindow( gameWinWidth, gameWinHeight, SDL_WINDOW_RESIZABLE );

    // create SDL renderer
    SDL_Renderer *sRenderer = CreateSDLRenderer( sWin, NULL, logWidth, logHeight );

    // instance of game resources
    GameResources gRes;
    gRes.loadResources( sRenderer );

    // set scale mode to nearest neighbor
    auto isScaledIdleTex = SDL_SetTextureScaleMode( gRes.idleTex, SDL_SCALEMODE_NEAREST );

    // set sprite movement (per second, not per frame)
    Uint64 startTicks = SDL_GetTicks( );

    // get keyboard state once (during window life-time)
    const bool *keys = SDL_GetKeyboardState( NULL );

    // instance of game system
    GameSystem gameSystem{ };

    // game entity player object
    GameEntity player;
    player.m_entityType = GameEntity::EntityType::player;
    player.m_texture = gRes.idleTex;
    player.m_animations = gRes.playerAnimations;
    player.m_currentAnimation = gRes.ANIM_PLAYER_IDLE;
    gameSystem.m_gameEntityLayers[GameSystem::LAYER_IDX_CHARACTERS].push_back( player );

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
                CleanUpResources( sWin, sRenderer );
                break;
            }
            // handle window resize event
            case SDL_EVENT_WINDOW_RESIZED:
            {
                // letter box logical presentation mode enables resizing sprites with ratio scale proportional to resized window size
                gameWinWidth = event.window.data1;
                gameWinHeight = event.window.data2;
                break;
            }
        }

        if (isScaledIdleTex)
        {
            // update all game entity objects
            for (auto layer : gameSystem.m_gameEntityLayers)
            {
                for (GameEntity obj : layer)
                {
                    if (obj.m_currentAnimation != -1)
                    {
                        obj.m_animations[obj.m_currentAnimation].stepAnimation( deltaTicks );
                    }
                }
            }
            // using the renderer (RGB_A)
            SDL_SetRenderDrawColor( sRenderer, clrRed, clrGreen, clrBlue, clrAlpha );
            // clear the renderer
            SDL_RenderClear( sRenderer );

            // draw all game entity objects
            for (auto layer : gameSystem.m_gameEntityLayers)
            {
                for (GameEntity obj : layer)
                {
                    DrawGameEntityObject( sRenderer, gameSystem, obj, deltaTicks );
                }
            }
        }

        // built-in swap-chain will (flip) back buffer to the front buffer and present renderer with updated changes
        SDL_RenderPresent( sRenderer );
    }

    // texture destroyed before exit, separated form cleanup resources function to enable extending texture functional within game program
    gRes.unLoadResources( );
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

static void CleanUpResources( SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer )
{
    SDL_DestroyRenderer( sdlRenderer );
    SDL_DestroyWindow( sdlWindow );
}
static void DrawGameEntityObject( SDL_Renderer *sdlRenderer, GameSystem &gameSystem, GameEntity &entityObject, float deltaTime )
{
    // sprite texture size
    const float spriteSize = 32.f;

    // updated src Pos X based on entity object current animation
    float srcX = entityObject.m_currentAnimation != -1
        ?
        entityObject.m_animations[entityObject.m_currentAnimation].getCurrentFrameToDisplay( ) * spriteSize
        : 0.0f;

    // control sprite per pixel (source float rect)
    SDL_FRect idleSrc{ srcX, 0, spriteSize, spriteSize };
    // control sprite per pixel (destination float rect)
    SDL_FRect idleDst{ entityObject.m_position.x, entityObject.m_position.y, spriteSize, spriteSize };
    // flip texture based on movement direction
    SDL_FlipMode flipMode = entityObject.m_direction == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    // render texture
    SDL_RenderTextureRotated( sdlRenderer, entityObject.m_texture, &idleSrc, &idleDst, 0, nullptr, flipMode );
}
