#pragma once

#include "GameTimer.h"

class GameAnimation
{
public:
    // default constructor
    GameAnimation( );
    // args constructor
    GameAnimation( int animatedFrameCount, float timeSpan );

public:
    void stepAnimation( float deltaTime );

public:
    // getters
    float getTimeSpan( ) const;
    float getCurrentFrameToDisplay( ) const;

private:
    GameTimer m_gameTimer;
    int m_animatedFrameCount;
};
