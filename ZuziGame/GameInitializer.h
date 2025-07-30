#pragma once

#include "GameBase.h"
#include "GameWindow.h"

class GameInitializer : public GameBase
{
public:
    GameInitializer( );
    virtual ~GameInitializer( ) override;
    void RunGame( );
private:
    std::unique_ptr< GameWindow> m_gameWindow{ };
    bool m_isGameRunning{ true };
};
