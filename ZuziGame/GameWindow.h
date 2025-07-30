#pragma once

#include "GameBase.h"
#include <iostream>
#include <Windows.h>

class GameWindow : public GameBase
{
public:
    GameWindow( );
    // override as virtual to let compiler find matching signatures in Base Class
    virtual ~GameWindow( ) override;

private:
    void* m_winHandle{ 0 };
};
