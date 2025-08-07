#include "GameTimer.h"

GameTimer::GameTimer( )
    :
    m_timeSpanLength( 0 ),
    m_elapsedTime( 0 ), // reset at start
    m_isTimeOut( false ) // reset at start
{ }

GameTimer::GameTimer( float timeSpanLength ) :
    m_timeSpanLength( timeSpanLength ),
    m_elapsedTime( 0 ), // reset at start
    m_isTimeOut( false ) // reset at start
{ }

bool GameTimer::stepGameTime( float deltaTime )
{
    m_elapsedTime += deltaTime;
    if (m_elapsedTime >= m_timeSpanLength)
    {
        m_elapsedTime -= m_timeSpanLength;
        m_isTimeOut = true;
        return m_isTimeOut;
    }
    return false;
}

void GameTimer::resetGameTimer( )
{
    m_elapsedTime = 0.f;
    m_isTimeOut = false;
}

bool GameTimer::getIsTimeout( ) const
{
    return m_isTimeOut;
}

float GameTimer::getElapsedTime( ) const
{
    return m_elapsedTime;
}

float GameTimer::getTimeSpanLength( ) const
{
    return m_timeSpanLength;
}
