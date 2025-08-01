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

GameAnimation::~GameAnimation( )
{ }

void GameAnimation::stepAnimation( float deltaTime )
{
    m_gameTimer.stepGameTime( deltaTime );
}

float GameAnimation::getTimeSpan( ) const
{
    return m_gameTimer.getGameTimeSpan( );
}

int GameAnimation::getCurrentFrameToDisplay( ) const
{
    return static_cast<int>(m_gameTimer.getElapsedTime( ) / m_gameTimer.getGameTimeSpan( ) * m_animatedFrameCount);
}
