#include "GameEntity.h"

GameEntity::GameEntity( )
    :
    u_entityUnion{ .um_level = LevelEntity( ) },
    m_flashTimer( 0.05f ),
    m_collider{ 0 },
    m_entityType( GameEntityType::Level ),
    m_acceleration( glm::vec2( 0 ) ),
    m_position( glm::vec2( 0 ) ),
    m_velocity( glm::vec2( 0 ) ),
    m_direction( 0 ),
    m_maxSpeedX( 0.f ),
    m_currentAnimation( -1 ),
    m_spriteFrame( 1 ),
    m_Dynamic( false ),
    m_grounded( false ),
    m_flash( false ),
    m_textureToDraw( nullptr )
{ }
