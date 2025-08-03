#include "GameEntity.h"

GameEntity::GameEntity( )
    :
    m_entityType( EntityType::level ),
    m_position( glm::vec2( 0 ) ),
    m_velocity( glm::vec2( 0 ) ),
    m_acceleration( glm::vec2( 0 ) ),
    m_direction( 1 ),
    m_currentAnimation( -1 ),
    m_texture( nullptr )
{ }
