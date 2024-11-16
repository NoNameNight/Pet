#include "Character.h"


#include <QScreen>

Character::Character() {}

void Character::onUpdate(float delta)
{
    m_state_machine.onUpdate(delta);

    float left = 0, right = 0, bottom = 0;
    QList<QScreen *> screenList = QGuiApplication::screens();
    for(int i = 0; i < screenList.size(); i++){
        QRect rc = screenList.at(i)->geometry();  //分辨率大小
        bottom = std::max(bottom, static_cast<float>(rc.bottom()));
        right = std::max(right, static_cast<float>(rc.right()));
        left = std::min(left, static_cast<float>(rc.left()));
    }
    FLOOR_Y = bottom;
    BORDER_LEFT_X = left;
    BORDER_RIGHT_X = right;


    if (m_enable_gravity)
    {
        m_velocity.y += GRAVITY * delta;
    }
    m_position += m_velocity * delta;

    Config* config = Config::instance();
    if (m_position.y >= bottom + config->character_foot_bottom)
    {
        m_position.y = bottom + config->character_foot_bottom;
        m_velocity.y = 0;
    }

    if (m_position.x <= left) { m_position.x = left; }
    if (m_position.x >= right) { m_position.x = right; }

    if (!m_current_animation) { return; }
    Animation& animation = //m_current_animation->right;
        (m_is_facing_left ? m_current_animation->left : m_current_animation->right);
    animation.onUpdate(delta);
    animation.setPosition(m_position);
}

void Character::onRender()
{
    if (!m_current_animation) { return; }
    ( m_is_facing_left ? m_current_animation->left : m_current_animation->right).onRender();
}

void Character::switchState(const std::string &id)
{
    m_state_machine.switchTo(id);
}

void Character::setAnimation(const std::string &id)
{
    m_current_animation = &m_animation_pool[id];
    m_current_animation->left.reset();
    m_current_animation->right.reset();
}
