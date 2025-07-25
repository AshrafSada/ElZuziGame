#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

struct SDLState
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    int winWidth, winHeight,
        logWidth, logHeight;
    Uint8 cR, cG, cB, cA;
};

// method signatures
static bool initializeGame(SDLState &state);
static void cleanup(SDLState &state);
