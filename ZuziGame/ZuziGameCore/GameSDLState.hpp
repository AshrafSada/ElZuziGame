#pragma once

#include <SDL3/SDL.h>

struct GameSDLState
{
public:
    SDL_Window *window{ };
    SDL_Renderer *renderer{ };
    int winWidth, winHeight, logWidth, logHeight;
    int clrRed, clrGreen, clrBlue, clrAlpha;
    bool isFullScreen;
    const bool *keysPressed;

public:
    GameSDLState( )
        :
        winWidth( 0 ), winHeight( 0 ), logWidth( 0 ), logHeight( 0 ),
        clrRed( 0 ), clrGreen( 0 ), clrBlue( 0 ), clrAlpha( 0 ),
        isFullScreen( false ),
        keysPressed( SDL_GetKeyboardState( NULL ) )
    { }
};
