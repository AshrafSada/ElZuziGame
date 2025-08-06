#include "GameEntity.h"

GameEntity::GameEntity( )
    :
    m_direction( 1 ),
    m_position( 0 ),
    m_velocity( 0 ),
    m_acceleration( 0 ),
    m_currentAnimation( -1 ),
    m_entityType( GameEntityType::Level ),
    m_textureToDraw( nullptr ),
    u_entityUnion{ .um_level = LevelEntity( ) }
{ }
