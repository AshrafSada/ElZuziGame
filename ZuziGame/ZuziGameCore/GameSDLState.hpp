#pragma once

#include <SDL3/SDL.h>

struct GameSDLState
{
public:
    int winWidth, winHeight, logWidth, logHeight;
    // surface colors RGB_A
    int clrRed, clrGreen, clrBlue, clrAlpha;
    SDL_Window *window;
    SDL_Renderer *renderer;
};
