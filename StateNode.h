#ifndef STATENODE_H
#define STATENODE_H

class StateNode
{
public:
    StateNode() = default;
    ~StateNode() = default;

    virtual void onEnter() = 0;
    virtual void onUpdate(float delta) = 0;
    virtual void onExit() = 0;
};

#endif // STATENODE_H
