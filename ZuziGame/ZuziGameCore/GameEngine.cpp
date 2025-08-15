#include "GameEngine.h"

bool GameEngine::InitializeSDL( )
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
SDL_Window *GameEngine::CreateSDLWindow( int width, int height, SDL_WindowFlags winFlags )
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
SDL_Renderer *GameEngine::CreateSDLRenderer( SDL_Window *sdlWin, const char *driverName, int logicalWidth, int logicalHeight )
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

// clean memory and destroy resource
void GameEngine::CleanUp( GameSDLState &sdlState )
{
    SDL_DestroyRenderer( sdlState.renderer );
    SDL_DestroyWindow( sdlState.window );
}

// Draw game entity object
void GameEngine::DrawGameEntity( GameSDLState &sdlState, GameState &gameState, GameEntity &entityObject, Uint64 deltaTime )
{
    // default sprite size
    const float spriteSize = 32.0f;

    // setting src X based on current animation and sprite size
    float srcX = entityObject.m_currentAnimation != -1
        ? ((float)entityObject.m_animations[entityObject.m_currentAnimation].getCurrentFrameCount( ) * spriteSize)
        : (entityObject.m_spriteFrame - 1) * spriteSize;

    // FRect src and dst
    SDL_FRect srcRect{ srcX, 0, spriteSize, spriteSize };
    SDL_FRect dstRect{ entityObject.m_position.x, entityObject.m_position.y, spriteSize, spriteSize };

    // flip mode ternary operator
    SDL_FlipMode flipMode = entityObject.m_direction == -1
        ? SDL_FLIP_HORIZONTAL
        : SDL_FLIP_NONE;

    // render texture rotated
    SDL_RenderTextureRotated( sdlState.renderer, entityObject.m_textureToDraw, &srcRect, &dstRect, 0, nullptr, flipMode );
}

void GameEngine::UpdateGameEntity( GameResources &gResources, GameSDLState &sdlState, GameState &gameState, GameEntity &entityObject, Uint64 deltaTime )
{
    // check if entity type is player
    if (entityObject.m_entityType == GameEntityType::Player)
    {
        // create float to hold current direction
        int currentDirection = 0;

        // check key pressed event for A,D
        if (sdlState.keysPressed[SDL_SCANCODE_A])
        {
            currentDirection += -1;
        }
        if (sdlState.keysPressed[SDL_SCANCODE_D])
        {
            currentDirection += 1;
        }

        if (currentDirection != 0)
        {
            // assign current direction to player entity
            entityObject.m_direction = currentDirection;
        }

        // switch on player state in the union
        switch (entityObject.u_entityUnion.um_player.m_playerState)
        {
            case PlayerState::Idle:
                // change the state to running
                if (currentDirection)
                {
                    entityObject.u_entityUnion.um_player.m_playerState = PlayerState::Running;
                }
                break;
            case PlayerState::Running:
                // change the state to idle
                if (!currentDirection)
                {
                    entityObject.u_entityUnion.um_player.m_playerState = PlayerState::Idle;
                }
                break;
        }

        // set velocity and acceleration based on max speed X and delta time
        entityObject.m_velocity += (float)currentDirection * entityObject.m_acceleration * (float)deltaTime;

        // update the position of the player based on delta time
        entityObject.m_position += entityObject.m_velocity * (float)deltaTime;
    }
}
