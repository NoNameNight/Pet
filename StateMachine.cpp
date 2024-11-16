#include "StateMachine.h"



void StateMachine::onUpdate(float delta)
{
    if (!m_current_state) { return; }
    if (m_need_init)
    {
        m_current_state->onEnter();
        m_need_init = false;
    }
    m_current_state->onUpdate(delta);
}

void StateMachine::setEnter(const std::string &id)
{
    m_current_state = m_state_pool[id];
}

void StateMachine::switchTo(const std::string &id)
{
    if (m_current_state) { m_current_state->onExit(); }
    m_current_state = m_state_pool[id];
    if (m_current_state) { m_current_state->onEnter(); }
}

void StateMachine::registerState(const std::string &id, StateNode *state_node)
{
    m_state_pool[id] = state_node;
}
