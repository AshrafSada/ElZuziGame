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
    // is time out getter
    bool getIsTimeout( ) const;
    // time span getter
    float getElapsedTime( ) const;
    // time span length getter
    float getTimeSpanLength( ) const;

private:
    // time span (length), elapsed time (time)
    float m_timeSpanLength, m_elapsedTime;
    bool m_isTimeOut;
};
