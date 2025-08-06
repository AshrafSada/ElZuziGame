#pragma once
#include "GameTimer.h"

class GameAnimation
{
public:
    // constructor
    GameAnimation( );
    // constructor args: animated frame count, time span length
    GameAnimation( int animateFrameCount, float timeSpanLength );

public:
    void stepAnimation( float deltaTime );

public:
    // time span length getter
    float getTimeSpanLength( ) const;
    // current animate frame count getter
    int getCurrentFrameCount( ) const;

private:
    // game timer instance member
    GameTimer m_gameTimer{ };
    // animate frame count member
    int m_animateFrameCount;
};
