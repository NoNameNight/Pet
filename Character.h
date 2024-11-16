#ifndef CHARACTER_H
#define CHARACTER_H

#include "Vector2.h"
#include "Animation.h"
#include "StateMachine.h"

#include <string>
#include <unordered_map>

class Character
{
public:
    Character();

    void setPosition(const Vector2& position)
    {
        m_position = position;
    }
    const Vector2& getPosition() const
    {
        return m_position;
    }
    void setVelocity(const Vector2& velocity)
    {
        m_velocity = velocity;
    }
    const Vector2& getVelocity() const
    {
        return m_velocity;
    }
    Vector2 getLogicCenter() const
    {
        return Vector2(m_position.x, m_position.y - m_logic_height / 2);
    }
    void setGravityEnabled(bool flag)
    {
        m_enable_gravity = flag;
    }
    bool isOnFloor() const
    {
        Config* config = Config::instance();
        return m_position.y - config->character_foot_bottom >= FLOOR_Y;
    }
    float getFloorY() const
    {
        return FLOOR_Y;
    }
    float getBorderLeftX() const
    {
        return BORDER_LEFT_X;
    }
    float getBorderRightX() const
    {
        return BORDER_RIGHT_X;
    }

    virtual void onUpdate(float delta);
    virtual void onRender();

    void switchState(const std::string& id);
    void setAnimation(const std::string& id);
protected:
    struct AnimationGroup
    {
        Animation left;
        Animation right;
    };
protected:
    float FLOOR_Y = 620;                                        //地板竖直方向坐标
    float BORDER_LEFT_X = 0;                                         //左边界坐标
    float BORDER_RIGHT_X = 1000;                                      //右边界坐标
    const float GRAVITY = 98.0 * 2;								//重力大小
protected:
    Vector2 m_position;													//角色脚底位置
    Vector2 m_velocity;													//角色速度
    float m_logic_height = 0;											//角色逻辑高度
    bool m_is_facing_left = false;										//角色是否向左
    StateMachine m_state_machine;										//角色逻辑状态机
    bool m_enable_gravity = true;										//启动重力模拟
    AnimationGroup* m_current_animation = nullptr;						//当前角色动画
    std::unordered_map<std::string, AnimationGroup> m_animation_pool;	//角色动画池
};


#endif // CHARACTER_H
