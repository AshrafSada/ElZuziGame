#pragma once

class GameBase
{
public:
    // constructor
    GameBase( );

    // destructor
    virtual ~GameBase( );
protected:
    // clean up memory
    GameBase( const GameBase & ) = delete;
    GameBase( const GameBase && ) = delete;
    GameBase operator=( const GameBase & ) = delete;
    GameBase operator=( const GameBase && ) = delete;
};
