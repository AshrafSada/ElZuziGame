#include <glad/glad.h>     // for loading and dispatching Open-GL
#include <stdio.h>         // For input/output functions like printf()
#include <stdlib.h>        // For general utilities like malloc(), free()
#include <stdbool.h>       // Fot boolean types support
#define SDL_MAIN_HANDLE    // Macro to tell SDL that this is the main entry point
#include <SDL3/SDL.h>      // SDL3 header file
#include <SDL3/SDL_main.h> // Redines main to SDL main, requires (arg count and arg value parameters)

int main(int argc, char *argv[])
{
    // Request OpenGL 4.6 Core Profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    // Use the Core Profile (no deprecated functions)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Enable forward-compatible context (optional but recommended)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    // Enable double buffering (for smooth rendering)
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Set depth buffer size (if using depth testing)
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Set stencil buffer size (if needed)
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Set multisampling (anti-aliasing)
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // 4x MSAA

    // create SDL window
    SDL_Window *wind = SDL_CreateWindow("Zuzi Game", 800, 600, SDL_WINDOW_OPENGL);

    if (!wind)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        EXIT_FAILURE;
    }

    // create GL context
    SDL_GLContext context = SDL_GL_CreateContext(wind);
    if (!context)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create GL context: %s\n", SDL_GetError());
        EXIT_FAILURE;
    }

    // Load Open-GL loader using GLAD
    int glLoader = gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);
    if (!glLoader)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create GL context: %s\n", SDL_GetError());
        EXIT_FAILURE;
    }

    puts("Open-GL loaded");

    puts("hello C");
    printf("hello game\n");

    EXIT_SUCCESS;
}
