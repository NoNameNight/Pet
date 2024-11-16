#include "PetStateNodes.h"

#include "Pet.h"
#include "CharacterManager.h"

PetStartState::PetStartState()
{
    m_timer.setOneShot(true);
    m_timer.setOnTimeout(
        [this](){
            Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
            pet->switchState("relax");
        }
        );
}

void PetStartState::onEnter()
{
    CharacterManager::instance()->getPet()->setAnimation("start");
    Config* config = Config::instance();
    float real_durtion = config->start_durtion * config->real_interval / config->row_interval;
    m_timer.setWaitTime(real_durtion);
    m_timer.restart();
}

void PetStartState::onUpdate(float delta)
{
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
    m_timer.onUpdate(delta);

    if(pet->getVelocity().y > 0)
    {
        pet->switchState("fall");
    }
}

void PetCarryState::onEnter()
{
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
    pet->setAnimation("fall");
    pet->setVelocity(Vector2(0,0));
    pet->setGravityEnabled(false);
}

void PetCarryState::onExit()
{
    CharacterManager::instance()->getPet()->setGravityEnabled(true);
}

void PetFallState::onEnter()
{
    CharacterManager::instance()->getPet()->setAnimation("fall");
}

void PetFallState::onUpdate(float delta)
{
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());

    if(pet->isOnFloor())
    {
        pet->switchState("relax");
    }
}

PetIdleState::PetIdleState()
{
    m_timer.setOneShot(true);
    m_timer.setOnTimeout(
        [this](){
            Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
            pet->switchState("relax");
        }
        );
}

void PetIdleState::onEnter()
{
    CharacterManager::instance()->getPet()->setAnimation("idle");

    float wait_time = range_random(TIME_MIN, TIME_MAX);
    Config* config = Config::instance();
    float real_durtion = config->idle_durtion * config->real_interval / config->row_interval;
    wait_time = round(wait_time / real_durtion) * real_durtion;
    m_timer.setWaitTime(wait_time);
    m_timer.restart();
}

void PetIdleState::onUpdate(float delta)
{
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());

    m_timer.onUpdate(delta);

    if(pet->getVelocity().y > 0)
    {
        pet->switchState("fall");
    }
}

PetMoveState::PetMoveState()
{
    m_timer.setOneShot(true);
    m_timer.setOnTimeout(
        [this](){
            Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
            pet->switchState("relax");
        }
        );
}

void PetMoveState::onEnter()
{
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());

    m_dir_probability = range_random(0, 100);
    if(m_dir_probability <= 50)
    {
        pet->setFacingLeft(false);
    }
    else
    {
        pet->setFacingLeft(true);
    }
    pet->setVelocity({m_dir_probability <= 50 ? SPEED_MOVE : -SPEED_MOVE, 0});

    pet->setAnimation("move");
    float wait_time = range_random(TIME_MIN, TIME_MAX);
    Config* config = Config::instance();
    float real_durtion = config->move_durtion * config->real_interval / config->row_interval;
    wait_time = round(wait_time / real_durtion) * real_durtion;
    m_timer.setWaitTime(wait_time);
    m_timer.restart();
}

void PetMoveState::onUpdate(float delta)
{
    Config* config = Config::instance();
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());

    m_timer.onUpdate(delta);

    if(pet->getPosition().x <= pet->getBorderLeftX() + config->border_padding)
    {
        pet->setFacingLeft(false);
        pet->setVelocity({SPEED_MOVE, 0});
    }
    if(pet->getPosition().x >= pet->getBorderRightX() - config->border_padding)
    {
        pet->setFacingLeft(true);
        pet->setVelocity({-SPEED_MOVE, 0});
    }

    if(pet->getVelocity().y > 0)
    {
        pet->switchState("fall");
    }
}

void PetMoveState::onExit()
{
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
    pet->setVelocity({ 0, 0 });
}

PetSkill2BeginState::PetSkill2BeginState()
{
    m_timer.setOneShot(true);
    m_timer.setOnTimeout(
        [this]() {
            Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
            pet->switchState("skill_2_loop");
        }
        );
}

void PetSkill2BeginState::onEnter()
{
    CharacterManager::instance()->getPet()->setAnimation("skill_2_begin");

    Config* config = Config::instance();
    float real_durtion = config->skill_2_begin_durtion * config->real_interval / config->row_interval;
    m_timer.setWaitTime(real_durtion);
    m_timer.restart();
}

void PetSkill2BeginState::onUpdate(float delta)
{
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
    m_timer.onUpdate(delta);

    if(pet->getVelocity().y > 0)
    {
        pet->switchState("fall");
    }
}

PetSkill2LoopState::PetSkill2LoopState()
{
    m_timer.setOneShot(true);
    m_timer.setOnTimeout(
        [this](){
            Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
            pet->switchState("relax");
        }
        );
}

void PetSkill2LoopState::onEnter()
{
    CharacterManager::instance()->getPet()->setAnimation("skill_2_loop");

    float wait_time = range_random(TIME_MIN, TIME_MAX);
    Config* config = Config::instance();
    float real_durtion = config->skill_2_loop_durtion * config->real_interval / config->row_interval;
    wait_time = round(wait_time / real_durtion) * real_durtion;
    m_timer.setWaitTime(wait_time);
    m_timer.restart();
}

void PetSkill2LoopState::onUpdate(float delta)
{
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());

    m_timer.onUpdate(delta);

    if(pet->getVelocity().y > 0)
    {
        pet->switchState("fall");
    }
}

PetInteractState::PetInteractState()
{
    m_timer.setOneShot(true);
    m_timer.setOnTimeout(
        [this]() {
            Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
            pet->switchState("relax");
        }
        );
}

void PetInteractState::onEnter()
{
    CharacterManager::instance()->getPet()->setAnimation("interact");

    Config* config = Config::instance();
    float real_durtion = config->interact_durtion * config->real_interval / config->row_interval;
    m_timer.setWaitTime(real_durtion);
    m_timer.restart();
}

void PetInteractState::onUpdate(float delta)
{
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());

    m_timer.onUpdate(delta);

    if(pet->getVelocity().y > 0)
    {
        pet->switchState("fall");
    }
}

PetSitState::PetSitState()
{
    m_timer.setOneShot(true);
    m_timer.setOnTimeout(
        [this]() {
            Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
            pet->switchState("relax");
        }
        );
}

void PetSitState::onEnter()
{
    CharacterManager::instance()->getPet()->setAnimation("sit");
    float wait_time = range_random(TIME_MIN, TIME_MAX);
    Config* config = Config::instance();
    float real_durtion = config->sit_durtion * config->real_interval / config->row_interval;
    wait_time = round(wait_time / real_durtion) * real_durtion;
    m_timer.setWaitTime(wait_time);
    m_timer.restart();
}

void PetSitState::onUpdate(float delta)
{
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());

    m_timer.onUpdate(delta);

    if(pet->getVelocity().y > 0)
    {
        pet->switchState("fall");
    }
}

PetSleepState::PetSleepState()
{
    m_timer.setOneShot(true);
    m_timer.setOnTimeout(
        [this]() {
            Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
            pet->switchState("relax");
        }
        );
}

void PetSleepState::onEnter()
{
    CharacterManager::instance()->getPet()->setAnimation("sleep");
    float wait_time = range_random(TIME_MIN, TIME_MAX);
    Config* config = Config::instance();
    float real_durtion = config->sleep_durtion * config->real_interval / config->row_interval;
    wait_time = round(wait_time / real_durtion) * real_durtion;
    m_timer.setWaitTime(wait_time);
    m_timer.restart();
}

void PetSleepState::onUpdate(float delta)
{
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());

    m_timer.onUpdate(delta);

    if(pet->getVelocity().y > 0)
    {
        pet->switchState("fall");
    }
}


PetRelaxState::PetRelaxState()
{
    m_timer.setOneShot(true);
    m_timer.setOnTimeout(
        [this]() {
            Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());
            int rand_num_in = range_random(0, ALL_PROBABILITY);
            qDebug() << rand_num_in;
            if(rand_num_in <= MOVE_PROBABILITY)
            {
                pet->switchState("move");
            }
            else if(rand_num_in <= MOVE_PROBABILITY + IDLE_PROBABILITY)
            {
                pet->switchState("idle");
            }
            else if(rand_num_in <= MOVE_PROBABILITY + IDLE_PROBABILITY + SKILL2_PROBABILITY)
            {
                pet->switchState("skill_2_begin");
            }
            else if(rand_num_in <= MOVE_PROBABILITY + IDLE_PROBABILITY + SKILL2_PROBABILITY + SIT_PROBABILITY)
            {
                pet->switchState("sit");
            }
            else if(rand_num_in <= MOVE_PROBABILITY + IDLE_PROBABILITY + SKILL2_PROBABILITY + SIT_PROBABILITY + SLEEP_PROBABILITY)
            {
                pet->switchState("sleep");
            }
        }
        );
}

void PetRelaxState::onEnter()
{
    ALL_PROBABILITY = MOVE_PROBABILITY + IDLE_PROBABILITY + SKILL2_PROBABILITY + SIT_PROBABILITY + SLEEP_PROBABILITY;
    CharacterManager::instance()->getPet()->setAnimation("relax");
    float wait_time = range_random(TIME_MIN, TIME_MAX);
    Config* config = Config::instance();
    float real_durtion = config->relax_durtion * config->real_interval / config->row_interval;
    wait_time = round(wait_time / real_durtion) * real_durtion;
    m_timer.setWaitTime(wait_time);
    m_timer.restart();
}

void PetRelaxState::onUpdate(float delta)
{
    Pet* pet = static_cast<Pet*>(CharacterManager::instance()->getPet());

    m_timer.onUpdate(delta);

    if(pet->getVelocity().y > 0)
    {
        pet->switchState("fall");
    }
}
