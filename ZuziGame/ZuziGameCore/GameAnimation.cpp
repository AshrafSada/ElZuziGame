#include <iostream>
#include "GameAnimation.h"

GameAnimation::GameAnimation( )
    :
    m_gameTimer( 0 ),
    m_animatedFrameCount( 0 )
{ }

GameAnimation::GameAnimation( int animatedFrameCount, float timeSpan )
    :
    m_animatedFrameCount( animatedFrameCount ),
    m_gameTimer( timeSpan )
{ }

void GameAnimation::stepAnimation( float deltaTime )
{
    m_gameTimer.stepGameTime( deltaTime );
}

float GameAnimation::getTimeSpan( ) const
{
    return m_gameTimer.getGameTimeSpan( );
}

float GameAnimation::getCurrentFrameToDisplay( ) const
{
    float elapsedTime = m_gameTimer.getElapsedTime( );
    float timeSpan = m_gameTimer.getGameTimeSpan( );
    float currentFrames = elapsedTime / timeSpan * (float)m_animatedFrameCount;
    return currentFrames;
}
