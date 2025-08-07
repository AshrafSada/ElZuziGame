#include "GameAnimation.h"

GameAnimation::GameAnimation( )
    :
    m_gameTimer( 0 ), // reset timer
    m_animateFrameCount( 0 ) // reset frame count
{ }

GameAnimation::GameAnimation( int animateFrameCount, float timeSpanLength )
    :
    m_animateFrameCount( animateFrameCount ),
    m_gameTimer( timeSpanLength )
{ }

void GameAnimation::stepAnimation( float deltaTime )
{
    m_gameTimer.stepGameTime( deltaTime );
}

float GameAnimation::getTimeSpanLength( ) const
{
    return m_gameTimer.getTimeSpanLength( );
}

int GameAnimation::getCurrentFrameCount( ) const
{
    int currentFrameCount = static_cast<int>(m_gameTimer.getElapsedTime( ) / m_gameTimer.getTimeSpanLength( ) * m_animateFrameCount);
    return currentFrameCount;
}

bool GameAnimation::getIsDoneAnimate( ) const
{
    return m_gameTimer.getIsTimeout( );
}
