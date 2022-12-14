#include "healer_enemy.h"

#include "collisions.h"
#include "entity_manager.h"

HealerEnemy::HealerEnemy(Vector2 position, const ResourceManager& RM) : Enemy(position)
{
    m_life = m_max_life = 70;
    m_reward = 5;
    m_damage = 5;
    m_speed = 200;
    m_texture = RM.getTexture(TextureType::HEALER_ENEMY_IDLE);
}

void HealerEnemy::update(float deltaTime)
{
    Enemy::update(deltaTime);

    getTarget();

    healTarget(deltaTime);
}

void    HealerEnemy::draw(GPLib* gp)
{
    if (m_target && m_target->m_life <= m_target->m_max_life)
        gpDrawLine(gp, m_position, m_target->getPosition(), {1, 0, 0, 1});
    else if (m_life <= m_max_life)
        gpDrawCircleFilled(gp, m_position, m_range, {0, 0, 1, 0.25f});

    Enemy::draw(gp);
}

void    HealerEnemy::getTarget()
{
    for (Enemy* enemy : m_entityManager->m_enemies)
    {
        if (enemy && enemy != this && enemy->m_life <= enemy->m_max_life &&
            c_circle_box(getCircle(), enemy->getRect()))
        {
            m_target = enemy;
            return;
        }
    }
}

void    HealerEnemy::healTarget(float deltaTime)
{
    if (m_target)
    {
        if (c_circle_box(getCircle(), m_target->getRect()) &&
        !m_target->m_shouldDestroy)
        {
            m_target->m_life += m_healRate * deltaTime;
        }
        else m_target = nullptr;
    }
    else if (m_life <= m_max_life)
    {
        m_life += m_healRate * deltaTime / 2;
    }
}

Circle  HealerEnemy::getCircle() const
{
    return Circle{m_range, m_position};
}
