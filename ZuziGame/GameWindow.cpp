#include "GameWindow.h"
#include <stdexcept>
#include <Windows.h>

const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 780;

// window message processing procedure
static LRESULT CALLBACK GameWinProcedure( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch (msg)
    {
        case WM_CLOSE:
            PostQuitMessage( 0 );
            break;
        default:
            return DefWindowProc( hWnd, msg, wParam, lParam );
    }
    return 0;
}

GameWindow::GameWindow( )
{
    // create instance of window class
    WNDCLASSEX windClass{ };

    // provide required properties before registering window class
    windClass.cbSize = sizeof( WNDCLASSEX );
    windClass.lpszClassName = L"ZUZIGameWinClass";
    windClass.lpfnWndProc = GameWinProcedure;

    // register window class and get window class id
    auto windClassId = RegisterClassEx( &windClass );
    if (!windClassId || windClassId == 0)
    {
        std::ignore = std::runtime_error( "Window class registration failed!" );
    }

    // special window properties
    LPCWSTR winNameTitle = L"ZUZI Game | Main Window";
    DWORD winStyle = WS_CAPTION | WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_SIZEBOX;
    RECT winRect{ 0, 0, WIN_WIDTH, WIN_HEIGHT };
    AdjustWindowRect( &winRect, winStyle, false );

    // create window from window instance and class id
    m_winHandle = CreateWindowEx( NULL, MAKEINTATOM( windClassId ), winNameTitle, winStyle,
        CW_USEDEFAULT, CW_USEDEFAULT,
        winRect.right - winRect.left, winRect.bottom - winRect.top,
        NULL, NULL, NULL, NULL );

    if (!m_winHandle || m_winHandle == 0)
    {
        std::ignore = std::runtime_error( "Window creation failed!" );
    }
    else
    {
        // call show window
        ShowWindow( static_cast<HWND>(m_winHandle), SW_SHOW );
    }
}

GameWindow::~GameWindow( )
{
    DestroyWindow( static_cast<HWND>(m_winHandle) );
}
