#pragma once

#include "GameTimer.h"

class GameAnimation
{
public:
    // default constructor
    GameAnimation( );
    // args constructor
    GameAnimation( int animatedFrameCount, float timeSpan );

    ~GameAnimation( );

public:
    void stepAnimation( float deltaTime );

public:
    // getters
    float getTimeSpan( ) const;
    int getCurrentFrameToDisplay( ) const;

private:
    GameTimer m_gameTimer;
    int m_animatedFrameCount;
};
