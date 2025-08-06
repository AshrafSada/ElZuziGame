#include "GameEngine.h"

GameEngine::GameEngine ( )
{ }

bool GameEngine::InitializeSDL ( )
{
    std::cout << "Game running ..." << std::endl;
    bool isSDLInitialized = SDL_Init ( SDL_INIT_VIDEO );

    // Initialize SDL with init video flag
    if ( !isSDLInitialized )
    {
        SDL_ShowSimpleMessageBox ( SDL_MESSAGEBOX_ERROR,
                                   "SDL init error",
                                   "SDL initialization failed!", nullptr );
    }
    return isSDLInitialized;
}

// create SDL window and returns pointer to created window
SDL_Window *GameEngine::CreateSDLWindow ( int width, int height, SDL_WindowFlags winFlags )
{
    SDL_Window *sWin = SDL_CreateWindow ( "ZUZI Game | Main Window", width, height, winFlags );
    if ( !sWin )
    {
        SDL_ShowSimpleMessageBox ( SDL_MESSAGEBOX_ERROR,
                                   "SDL window error",
                                   "SDL window creation failed!", sWin );
    }
    return sWin;
}

// create SDL renderer and return pointer to created renderer
SDL_Renderer *GameEngine::CreateSDLRenderer ( SDL_Window *sdlWin, const char *driverName, int logicalWidth, int logicalHeight )
{
    // create SDL Renderer (renderer driver name = NULL, let SDL find the best one to use)
    SDL_Renderer *sRenderer = SDL_CreateRenderer ( sdlWin, driverName );
    if ( !sRenderer )
    {
        SDL_ShowSimpleMessageBox ( SDL_MESSAGEBOX_ERROR,
                                   "SDL renderer error",
                                   "SDL renderer creation failed!", sdlWin );
    }

    // set logical renderer presentation letter box to scale objects per window current size
    SDL_SetRenderLogicalPresentation ( sRenderer, logicalWidth, logicalHeight,
                                       SDL_RendererLogicalPresentation::SDL_LOGICAL_PRESENTATION_LETTERBOX );

    return sRenderer;
}

// clean memory and destroy resource
void GameEngine::CleanUp ( GameSDLState &sdlState )
{
    SDL_DestroyRenderer ( sdlState.renderer );
    SDL_DestroyWindow ( sdlState.window );
}

// Draw game entity object
void GameEngine::DrawGameEntity ( GameSDLState &sdlState, GameState &gameState, GameEntity &entityObject, float deltaTime )
{
    // default sprite size
    const float spriteSize = 32.f;

    // setting src X based on current animation and sprite size
    float srcX = entityObject.m_currentAnimation != -1
        ? ( ( float )entityObject.m_animations[ entityObject.m_currentAnimation ].getCurrentFrameCount ( ) * spriteSize )
        : 0.f;

    // FRect src and dst
    SDL_FRect srcRect{ srcX, 0, spriteSize, spriteSize };
    SDL_FRect dstRect{ entityObject.m_position.x, entityObject.m_position.y, spriteSize, spriteSize };

    // flip mode ternary operator
    SDL_FlipMode flipMode = entityObject.m_direction == -1
        ? SDL_FLIP_HORIZONTAL
        : SDL_FLIP_NONE;

    // render texture rotated
    SDL_RenderTextureRotated ( sdlState.renderer, entityObject.m_textureToDraw, &srcRect, &dstRect, 0, NULL, flipMode );
}

void GameEngine::UpdateGameEntity ( GameResources &gResources, GameSDLState &sdlState, GameState &gameState, GameEntity &entityObject, float deltaTime )
{
    // TODO: implement
    if ( entityObject.m_entityType == GameEntityType::Player )
    {
    }
}

// technical hardware info query
void GameEngine::getHardwareInfo ( )
{
    // get number of audio drivers
    int audioDrivers = SDL_GetNumAudioDrivers ( );
    std::cout << "Audio drivers: " << audioDrivers << std::endl;

    for ( int i = 0; i < audioDrivers; i++ )
    {
        std::cout << "Audio driver " << i + 1 << " Name: " << SDL_GetAudioDriver ( i ) << std::endl;
    }

    // get number of GPU drivers
    int videoDrivers = SDL_GetNumGPUDrivers ( );
    std::cout << "Video GPU drivers: " << videoDrivers << std::endl;

    for ( int i = 0; i < videoDrivers; i++ )
    {
        std::cout << "Video driver " << i + 1 << " Name: " << SDL_GetVideoDriver ( i ) << std::endl;
    }

    // get system RAM size
    auto sysRAM = SDL_GetSystemRAM ( );
    std::cout << "System RAM size: " << sysRAM << "MB" << std::endl;
}
