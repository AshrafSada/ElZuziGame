#pragma once

// Game timer controls animation timing and game progress
class GameTimer
{
public:
    GameTimer( );
    GameTimer( float timeSpanLength );

public:
    bool stepGameTime( float deltaTime );
    void resetGameTimer( );

public:
    // getters
    bool getIsTimeout( ) const;
    float getElapsedTime( ) const;
    float getTimeSpanLength( ) const;

private:
    float m_timeSpanLength, m_elapsedTime;
    bool m_isTimeOut;
};
