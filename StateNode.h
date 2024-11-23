#ifndef STATENODE_H
#define STATENODE_H

class StateNode
{
public:
    StateNode(void* character)
        :m_character(character)
    {}
    ~StateNode() = default;

    virtual void onEnter() = 0;
    virtual void onUpdate(float delta) = 0;
    virtual void onExit() = 0;
protected:
    void* m_character;
};

#endif // STATENODE_H
