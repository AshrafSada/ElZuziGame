#include "GameEngine.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

static void CleanUpResources( SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer );
static bool InitializeSDL( );
static SDL_Window *CreateSDLWindow( int width, int height, SDL_WindowFlags winFlags );
static SDL_Renderer *CreateSDLRenderer( SDL_Window *sdlWin, const char *driverName, int logicalWidth, int logicalHeight );

// NOTE: required by SDL  argc: argument count, argv: argument value
int main( int argc, char *argv[] )
{
    InitializeSDL( );

    // win width
    int gameWinWidth = 1280;
    int gameWinHeight = 960;
    // surface color
    int clrRed = 30;
    int clrGreen = 60;
    int clrBlue = 56;
    int clrAlpha = 255;
    // renderer presentation surface
    int logWidth = 960, logHeight = 480;
    // idle texture size
    float idleTexWidth = 32.f, idleTexHeight = 32.f;
    // idle text position on the renderer surface
    float idleTexPosX = (float)logWidth / 2;
    const float idleTexPosY = (float)logHeight - idleTexHeight;

    // create SDL window
    SDL_Window *sWin = CreateSDLWindow( gameWinWidth, gameWinHeight, SDL_WINDOW_RESIZABLE );

    // create SDL renderer
    SDL_Renderer *sRenderer = CreateSDLRenderer( sWin, NULL, logWidth, logHeight );

    // loading game assets using SDL Image Texture
    auto spriteTexPath = ".\\.\\GameAssets\\idle.png";
    SDL_Texture *idleTex = IMG_LoadTexture( sRenderer, spriteTexPath );
    // set scale mode to nearest neighbor
    auto isScaledIdleTex = SDL_SetTextureScaleMode( idleTex, SDL_SCALEMODE_NEAREST );
    // control sprite per pixel (source float rect)
    SDL_FRect idleSrc{ 0, 0, idleTexWidth, idleTexHeight };

    // set sprite movement (per second, not per frame)
    bool flipHor = false;
    float difficultyLevel = 0.75f; // 0.5 = easy
    Uint64 startTicks = SDL_GetTicks( );
    float playerPosX = 0;
    float playerSpeedRate = 0.005f;
    float playerMoveRate = 0;

    // get keyboard state once (during window life-time)
    const bool *keys = SDL_GetKeyboardState( NULL );

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

        // handle key pressed events for ASDW
        if (keys[SDL_SCANCODE_A])
        {
            flipHor = true;
            playerMoveRate -= (playerSpeedRate * deltaTicks) * difficultyLevel;
        }
        if (keys[SDL_SCANCODE_D])
        {
            flipHor = false;
            playerMoveRate += (playerSpeedRate * deltaTicks) * difficultyLevel;
        }
        playerPosX = playerMoveRate;

        // using the renderer (RGB_A)
        SDL_SetRenderDrawColor( sRenderer, clrRed, clrGreen, clrBlue, clrAlpha );
        // clear the renderer
        SDL_RenderClear( sRenderer );
        // control sprite per pixel (destination float rect)
        SDL_FRect idleDst{ playerPosX, idleTexPosY, idleTexWidth, idleTexHeight };
        if (isScaledIdleTex)
        {
            // flip texture based on movement direction
            SDL_RenderTextureRotated( sRenderer, idleTex, &idleSrc, &idleDst, 0, 0, flipHor ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE );
        }

        // built-in swap-chain will (flip) back buffer to the front buffer and present renderer with updated changes
        SDL_RenderPresent( sRenderer );
    }

    // texture destroyed before exit, separated form cleanup resources function to enable extending texture functional within game program
    SDL_DestroyTexture( idleTex );
    return 0;
}

// implement in order of allocation (FIFO)
static void CleanUpResources( SDL_Window *sdlWindow, SDL_Renderer *sdlRenderer )
{
    SDL_DestroyRenderer( sdlRenderer );
    SDL_DestroyWindow( sdlWindow );
}

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
