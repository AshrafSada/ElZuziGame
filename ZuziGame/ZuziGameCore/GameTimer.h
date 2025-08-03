#pragma once

// Game timer controls animation timing and game progress
class GameTimer
{
public:
    GameTimer( float timeSpan );

public:
    void stepGameTime( float deltaTime );
    void resetGameTimer( );

public:
    // getters
    bool getIsTimeout( ) const;
    float getElapsedTime( ) const;
    float getGameTimeSpan( ) const;

private:
    float m_gameTimeSpan, m_elapsedTime;
    bool m_isTimeOut;
};
