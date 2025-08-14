#pragma once

#include <SDL3/SDL.h>

struct GameSDLState
{
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    int winWidth, winHeight, logWidth, logHeight;
    int clrRed, clrGreen, clrBlue, clrAlpha;
    bool isFullScreen;
    const bool *keysPressed;
};
