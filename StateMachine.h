#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "StateNode.h"

#include <string>
#include <unordered_map>

class StateMachine
{
public:
    StateMachine() = default;
    ~StateMachine() = default;

    void onUpdate(float delta);

    void setEnter(const std::string& id);
    void switchTo(const std::string& id);
    void registerState(const std::string& id, StateNode* state_node); //注册新状态

private:
    bool m_need_init = true;
    StateNode* m_current_state = nullptr; //当前激活节点
    std::unordered_map<std::string, StateNode*> m_state_pool;
};

#endif // STATEMACHINE_H
