#include "GameInitializer.h"
#include <Windows.h>

GameInitializer::GameInitializer( )
{
    m_gameWindow = std::make_unique<GameWindow>( );
}

GameInitializer::~GameInitializer( )
{ }

void GameInitializer::RunGame( )
{
    // handle window event messages
    MSG msg{ };

    // Game loop
    while (m_isGameRunning)
    {
        // handling window events with peek message
        while (PeekMessage( &msg, nullptr, 0, 0, PM_REMOVE ))
        {
            switch (msg.message)
            {
                case WM_QUIT:
                    m_isGameRunning = false;
                    break;
            }

            // translate window event message
            TranslateMessage( &msg );

            // dispatch message to window procedure
            DispatchMessageW( &msg );
        }
        // ease the CPU load by suspending execution for 1ms
        Sleep( 1 );
    }
}
