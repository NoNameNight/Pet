#ifndef PET_H
#define PET_H

#include "Character.h"

class Pet : public Character
{
public:
    Pet();
    void onUpdate(float delta) override;
    void onRender() override;
    void setFacingLeft(bool flag)
    {
        m_is_facing_left = flag;
    }

    bool getFacingLeft() const
    {
        return m_is_facing_left;
    }
protected:
};

#endif // PET_H
