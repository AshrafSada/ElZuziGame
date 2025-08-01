#include "GamePreferences.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

static void CleanUpResources( SDL_Window* sdlWindow, SDL_Renderer* sdlRenderer );

// NOTE: required by SDL  argc: argument count, argv: argument value
int main( int argc, char* argv[] )
{
    std::cout << "Game running ..." << "\\n";

    // Initialize SDL with init video flag
    if (!SDL_Init( SDL_INIT_VIDEO ))
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,
            "SDL init error",
            "SDL initialization failed!", nullptr );
        return 1;
    }

    // game preferences instance
    GamePreferences gPref{ };
    gPref.gameWinWidth = 1020;
    gPref.gameWinHeight = 780;
    gPref.clrRed = 98;
    gPref.clrGreen = 198;
    gPref.clrBlue = 98;
    gPref.clrAlpha = 255;

    // create SDL window pointer
    SDL_Window* sWin = SDL_CreateWindow( "ZUZI Game | Main Window", gPref.gameWinWidth, gPref.gameWinHeight, 0 );
    if (!sWin)
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,
            "SDL window error",
            "SDL window creation failed!", sWin );
        return 2;
    }

    // create SDL Renderer (renderer driver name = NULL, let SDL find the best one to use)
    SDL_Renderer* sRenderer = SDL_CreateRenderer( sWin, NULL );
    if (!sRenderer)
    {
        SDL_ShowSimpleMessageBox( SDL_MESSAGEBOX_ERROR,
            "SDL renderer error",
            "SDL renderer creation failed!", sWin );
        return 2;
    }

    // loading game assets using SDL Image Texture
    const char* texFilePath = "..\\..\\GameAssets\\idle.png";
    SDL_Texture* idleTex = IMG_LoadTexture( sRenderer, texFilePath );

    // create window loop
    bool isGameRunning = true;
    while (isGameRunning)
    {
        // handling window events
        SDL_Event event{ 0 };
        SDL_PollEvent( &event );
        switch (event.type)
        {
            // handle quit event
            case SDL_EVENT_QUIT:
            {
                isGameRunning = false;
                std::cout << "Resource clean up started ..." << "\\n";
                CleanUpResources( sWin, sRenderer );
                break;
            }
        }
        // using the renderer (RGB_A)
        SDL_SetRenderDrawColor( sRenderer, gPref.clrRed, gPref.clrGreen, gPref.clrBlue, gPref.clrAlpha );
        // clear the renderer
        SDL_RenderClear( sRenderer );
        // render texture
        SDL_RenderTexture( sRenderer, idleTex, NULL, NULL );
        // built-in swap-chain will (flip) back buffer to the front buffer and present renderer with updated changes
        SDL_RenderPresent( sRenderer );
    }

    // texture destroyed before exit, separated form cleanup resources function to enable extending texture functional within game program
    SDL_DestroyTexture( idleTex );
    return 0;
}

// implement in order of allocation (FIFO)
static void CleanUpResources( SDL_Window* sdlWindow, SDL_Renderer* sdlRenderer )
{
    SDL_DestroyRenderer( sdlRenderer );
    SDL_DestroyWindow( sdlWindow );
}
