#include "GameTimer.h"

GameTimer::GameTimer( float timeSpan )
    :
    m_gameTimeSpan( timeSpan ),
    m_elapsedTime( 0 ), // reset at start
    m_isTimeOut( false ) // reset at start
{ }

GameTimer::~GameTimer( )
{ }

void GameTimer::stepGameTime( float deltaTime )
{
    m_elapsedTime += deltaTime;
    if (m_elapsedTime >= m_gameTimeSpan)
    {
        m_elapsedTime -= m_gameTimeSpan;
        m_isTimeOut = true;
    }
}

void GameTimer::resetGameTimer( )
{
    m_elapsedTime = 0.f;
}

bool GameTimer::getIsTimeout( ) const
{
    return m_isTimeOut;
}

float GameTimer::getElapsedTime( ) const
{
    return m_elapsedTime;
}

float GameTimer::getGameTimeSpan( ) const
{
    return m_gameTimeSpan;
}
