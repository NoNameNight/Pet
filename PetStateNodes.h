#ifndef PETSTATENODES_H
#define PETSTATENODES_H

#include "Timer.h"
#include "StateNode.h"

class PetStartState : public StateNode
{
public:
    PetStartState();
    ~PetStartState() = default;

    void onEnter() override;
    void onUpdate(float delta) override;
    void onExit() override {}
private:
    Timer m_timer;
};

class PetCarryState : public StateNode
{
public:
    PetCarryState() = default;
    ~PetCarryState() = default;

    void onEnter() override;
    void onUpdate(float delta) override {};
    void onExit() override;
};

class PetFallState : public StateNode
{
public:
    PetFallState() = default;
    ~PetFallState() = default;

    void onEnter() override;
    void onUpdate(float delta) override;
    void onExit() override {}
};

class PetIdleState : public StateNode
{
public:
    PetIdleState();
    ~PetIdleState() = default;

    void onEnter() override;
    void onUpdate(float delta) override;
    void onExit() override {}
private:
    Timer m_timer;

    // const int KEEP_PROBABILITY = 985; // 0-1000; 保持此节点的概率
    const float TIME_MIN = 8.f;
    const float TIME_MAX = 16.f;
};

class PetMoveState : public StateNode
{
public:
    PetMoveState();
    ~PetMoveState() = default;

    void onEnter() override;
    void onUpdate(float delta) override;
    void onExit() override;
private:
    Timer m_timer;

    const float SPEED_MOVE = 50.f;
    int m_dir_probability = 0;
    // const int KEEP_PROBABILITY = 980; // 0-1000; 保持此节点的概率
    const float TIME_MIN = 6.f;
    const float TIME_MAX = 18.f;

    // // 以下概率为全部相加概率占比
    // const int RELAX_PROBABILITY = 10; // RELAX 的概率
};

class PetSkill2BeginState : public StateNode
{
public:
    PetSkill2BeginState();
    ~PetSkill2BeginState() = default;

    void onEnter() override;
    void onUpdate(float delta) override;
    void onExit() override {};
private:
    Timer m_timer;
};

class PetSkill2LoopState : public StateNode
{
public:
    PetSkill2LoopState();
    ~PetSkill2LoopState() = default;

    void onEnter() override;
    void onUpdate(float delta) override;
    void onExit() override {};
private:
    Timer m_timer;

    const float TIME_MIN = 12.f;
    const float TIME_MAX = 24.f;
};

class PetInteractState : public StateNode
{
public:
    PetInteractState();
    ~PetInteractState() = default;

    void onEnter() override;
    void onUpdate(float delta) override;
    void onExit() override {};
private:
    Timer m_timer;
};

class PetSitState : public StateNode
{
public:
    PetSitState();
    ~PetSitState() = default;

    void onEnter() override;
    void onUpdate(float delta) override;
    void onExit() override {}
private:
    Timer m_timer;

    // const int KEEP_PROBABILITY = 995; // 0-1000; 保持此节点的概率
    const float TIME_MIN = 10.f;
    const float TIME_MAX = 15.f;
};

class PetSleepState : public StateNode
{
public:
    PetSleepState();
    ~PetSleepState() = default;

    void onEnter() override;
    void onUpdate(float delta) override;
    void onExit() override {}
private:
    Timer m_timer;

    // const int KEEP_PROBABILITY = 995; // 0-1000; 保持此节点的概率
    const float TIME_MIN = 15.f;
    const float TIME_MAX = 25.f;
};

class PetRelaxState : public StateNode
{
public:
    PetRelaxState();
    ~PetRelaxState() = default;

    void onEnter() override;
    void onUpdate(float delta) override;
    void onExit() override {}
private:
    Timer m_timer;

    // const int KEEP_PROBABILITY = 995; // 0-1000; 保持此节点的概率
    const float TIME_MIN = 10.f;
    const float TIME_MAX = 15.f;

    // 以下概率为全部相加概率占比
    const int MOVE_PROBABILITY = 100; // MOVE 的概率占比
    const int IDLE_PROBABILITY = 100; // IDLE 的概率占比
    const int SKILL2_PROBABILITY = 100; // SKILL2 的概率占比
    const int SIT_PROBABILITY = 60; // SIT 的概率占比
    const int SLEEP_PROBABILITY = 70; // SLEEP 的概率占比

    int ALL_PROBABILITY = 500; // 全概率和
};

#endif // PETSTATENODES_H
