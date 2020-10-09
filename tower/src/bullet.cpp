#include "bullet.h"

Bullet::Bullet(Vector2 position, Enemy* enemy, float damage, const ResourceManager& RM)
: Entity(position), m_target(enemy)
{
    m_texture = RM.get_texture(TextureType::BULLET);
    m_speed = 250;
    m_damage = damage;
}

void Bullet::update() 
{
    move();
}

void Bullet::move()
{
    m_direction = (m_target->get_position() - m_position).normalize();
    m_position += m_direction * m_speed * delta_time;
}