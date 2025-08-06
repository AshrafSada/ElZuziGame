#include "GameAnimation.h"

GameAnimation::GameAnimation( )
    :
    m_gameTimer( 0 ),
    m_animateFrameCount( 0 )
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
    return 0.0f;
}

int GameAnimation::getCurrentFrameCount( ) const
{
    int currentFrameCount = static_cast<int>(m_gameTimer.getElapsedTime( ) / m_gameTimer.getTimeSpanLength( ) * m_animateFrameCount);
    return currentFrameCount;
}
