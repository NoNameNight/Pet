#include "Pet.h"
#include "ResourcesManager.h"
// #include "PetStateNodes.h"

#include <QScreen>

Pet::Pet()
{
    float left = 0, right = 0, bottom = 0;
    QList<QScreen *> screenList = QGuiApplication::screens();
    for(int i = 0; i < screenList.size(); i++){
        QRect rc = screenList.at(i)->geometry();  //分辨率大小
        bottom = std::max(bottom, static_cast<float>(rc.bottom()));
        right = std::max(right, static_cast<float>(rc.right()));
        left = std::min(left, static_cast<float>(rc.left()));
    }

    m_is_facing_left = false;
    m_position = { 300, bottom + Config::instance()->character_foot_bottom };
    m_logic_height = 150;

    float interval = Config::instance()->real_interval;
    {
        {
            AnimationGroup& animation = m_animation_pool["start"];

            Animation& animation_left = animation.left;
            animation_left.setInterval(interval);
            animation_left.setLoop(false);
            animation_left.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_left.addFrame(ResourcesManager::instance()->findAtlas("skadi_start_left"));

            Animation& animation_right = animation.right;
            animation_right.setInterval(interval);
            animation_right.setLoop(false);
            animation_right.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_right.addFrame(ResourcesManager::instance()->findAtlas("skadi_start_right"));
        }

        {
            AnimationGroup& animation = m_animation_pool["interact"];

            Animation& animation_left = animation.left;
            animation_left.setInterval(interval);
            animation_left.setLoop(false);
            animation_left.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_left.addFrame(ResourcesManager::instance()->findAtlas("skadi_interact_left"));

            Animation& animation_right = animation.right;
            animation_right.setInterval(interval);
            animation_right.setLoop(false);
            animation_right.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_right.addFrame(ResourcesManager::instance()->findAtlas("skadi_interact_right"));
        }

        {
            AnimationGroup& animation = m_animation_pool["skill_2_begin"];

            Animation& animation_left = animation.left;
            animation_left.setInterval(interval);
            animation_left.setLoop(false);
            animation_left.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_left.addFrame(ResourcesManager::instance()->findAtlas("skadi_skill_2_begin_left"));

            Animation& animation_right = animation.right;
            animation_right.setInterval(interval);
            animation_right.setLoop(false);
            animation_right.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_right.addFrame(ResourcesManager::instance()->findAtlas("skadi_skill_2_begin_right"));
        }

        {
            AnimationGroup& animation = m_animation_pool["skill_2_loop"];

            Animation& animation_left = animation.left;
            animation_left.setInterval(interval);
            animation_left.setLoop(true);
            animation_left.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_left.addFrame(ResourcesManager::instance()->findAtlas("skadi_skill_2_loop_left"));

            Animation& animation_right = animation.right;
            animation_right.setInterval(interval);
            animation_right.setLoop(true);
            animation_right.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_right.addFrame(ResourcesManager::instance()->findAtlas("skadi_skill_2_loop_right"));
        }

        {
            AnimationGroup& animation = m_animation_pool["move"];

            Animation& animation_left = animation.left;
            animation_left.setInterval(interval);
            animation_left.setLoop(true);
            animation_left.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_left.addFrame(ResourcesManager::instance()->findAtlas("skadi_move_left"));

            Animation& animation_right = animation.right;
            animation_right.setInterval(interval);
            animation_right.setLoop(true);
            animation_right.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_right.addFrame(ResourcesManager::instance()->findAtlas("skadi_move_right"));
        }

        {
            AnimationGroup& animation = m_animation_pool["fall"];

            Animation& animation_left = animation.left;
            animation_left.setInterval(interval);
            animation_left.setLoop(true);
            animation_left.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_left.addFrame(ResourcesManager::instance()->findAtlas("skadi_fall_left"));

            Animation& animation_right = animation.right;
            animation_right.setInterval(interval);
            animation_right.setLoop(true);
            animation_right.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_right.addFrame(ResourcesManager::instance()->findAtlas("skadi_fall_right"));
        }

        {
            AnimationGroup& animation = m_animation_pool["idle"];

            Animation& animation_left = animation.left;
            animation_left.setInterval(interval);
            animation_left.setLoop(true);
            animation_left.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_left.addFrame(ResourcesManager::instance()->findAtlas("skadi_idle_left"));

            Animation& animation_right = animation.right;
            animation_right.setInterval(interval);
            animation_right.setLoop(true);
            animation_right.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_right.addFrame(ResourcesManager::instance()->findAtlas("skadi_idle_right"));
        }

        {
            AnimationGroup& animation = m_animation_pool["relax"];

            Animation& animation_left = animation.left;
            animation_left.setInterval(interval);
            animation_left.setLoop(true);
            animation_left.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_left.addFrame(ResourcesManager::instance()->findAtlas("skadi_relax_left"));

            Animation& animation_right = animation.right;
            animation_right.setInterval(interval);
            animation_right.setLoop(true);
            animation_right.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_right.addFrame(ResourcesManager::instance()->findAtlas("skadi_relax_right"));
        }

        {
            AnimationGroup& animation = m_animation_pool["sit"];

            Animation& animation_left = animation.left;
            animation_left.setInterval(interval);
            animation_left.setLoop(true);
            animation_left.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_left.addFrame(ResourcesManager::instance()->findAtlas("skadi_sit_left"));

            Animation& animation_right = animation.right;
            animation_right.setInterval(interval);
            animation_right.setLoop(true);
            animation_right.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_right.addFrame(ResourcesManager::instance()->findAtlas("skadi_sit_right"));
        }

        {
            AnimationGroup& animation = m_animation_pool["sleep"];

            Animation& animation_left = animation.left;
            animation_left.setInterval(interval);
            animation_left.setLoop(true);
            animation_left.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_left.addFrame(ResourcesManager::instance()->findAtlas("skadi_sleep_left"));

            Animation& animation_right = animation.right;
            animation_right.setInterval(interval);
            animation_right.setLoop(true);
            animation_right.setAnchorMode(Animation::AnchorMode::BottomCentered);
            animation_right.addFrame(ResourcesManager::instance()->findAtlas("skadi_sleep_right"));
        }
    }

    // {
    //     m_state_machine.registerState("start", new PetStartState());
    //     m_state_machine.registerState("interact", new PetInteractState());
    //     m_state_machine.registerState("carry", new PetCarryState());
    //     m_state_machine.registerState("fall", new PetFallState());
    //     m_state_machine.registerState("idle", new PetIdleState());
    //     m_state_machine.registerState("move", new PetMoveState());
    //     m_state_machine.registerState("sit", new PetSitState());
    //     m_state_machine.registerState("sleep", new PetSleepState());
    //     m_state_machine.registerState("relax", new PetRelaxState());
    //     m_state_machine.registerState("skill_2_begin", new PetSkill2BeginState());
    //     m_state_machine.registerState("skill_2_loop", new PetSkill2LoopState());

    //     m_state_machine.setEnter("start");

    // }
    m_is_facing_left = true;
}

void Pet::onUpdate(float delta)
{
    if (abs(m_velocity.x) >= 0.0001f)
    {
        m_is_facing_left = (m_velocity.x < 0);
    }
    Character::onUpdate(delta);
}

void Pet::onRender()
{
    Character::onRender();
}
