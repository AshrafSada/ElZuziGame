#include "ZuziGame.h"

int main(int argc, char *argv[])
{
// instantiate SDLState
    SDLState state{ 0 };
    state.winWidth = 1600;
    state.winHeight = 960;
    state.logWidth = 680;
    state.logHeight = 320;
    state.cR = 20;
    state.cG = 10;
    state.cB = 30;
    state.cA = 255;

    if (!initializeGame(state))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Initialization Error", "An error occurred while initializing the game", nullptr);
        return -1;
    }

// configure SDL presentation and renderer
    bool logicalPresentConfigured = SDL_SetRenderLogicalPresentation(state.renderer, state.logWidth, state.logHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    bool renderDrawColorSet = SDL_SetRenderDrawColor(state.renderer, state.cR, state.cG, state.cB, state.cA);

    // load texture
    SDL_Texture *idleTexture = IMG_LoadTexture(state.renderer, "Assets/idle.png");
    // scale texture to nearest instead of linear(causes blur)
    bool idleTextureScaled = SDL_SetTextureScaleMode(idleTexture, SDL_SCALEMODE_NEAREST);
    // texture position (src)
    SDL_FRect texSrc{
        .x = 0.f,
        .y = 0.f,
        .w = 32.f,
        .h = 32.f,
    };
    // texture size (dst)
    SDL_FRect texDst{
        .x = 0.f,
        .y = 0.f,
        .w = 32.f,
        .h = 32.f,
    };

    // run SDL window in loop
    bool runWindow = true;
    while (runWindow)
    {
    // handle window events
        SDL_Event event = { 0 };
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            // handle close event
                case SDL_EVENT_QUIT:
                    runWindow = false;
                    cleanup(state);
                    break;
                    // handle resize window
                case SDL_EVENT_WINDOW_RESIZED:
                    state.winWidth = event.window.data1;
                    state.winHeight = event.window.data2;
                    break;
            }
        }

        if (logicalPresentConfigured
            && renderDrawColorSet
            && idleTextureScaled) {
            SDL_RenderClear(state.renderer);
            SDL_RenderTexture(state.renderer, idleTexture, &texSrc, &texDst);
            SDL_RenderPresent(state.renderer);
        }
    }





    SDL_DestroyTexture(idleTexture);
    cleanup(state);

    return 0;
}

static bool initializeGame(SDLState &state)
{
    bool initSuccess = true;

    // initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Video Error", "An error occurred while initializing SDL Video", nullptr);
        initSuccess = false;
    }

// create SDL window
    state.window = SDL_CreateWindow("EL ZUZI Game", state.winWidth, state.winHeight, SDL_WINDOW_RESIZABLE);
    if (!state.window)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game Window Error", "An error occurred while creating game window", state.window);
        initSuccess = false;
    }

// create renderer
    state.renderer = SDL_CreateRenderer(state.window, nullptr);
    if (!state.renderer)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game Renderer Error", "An error occurred while creating game renderer", state.window);
        initSuccess = false;
    }
    return initSuccess;
}

static void cleanup(SDLState &state)
{
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
}
