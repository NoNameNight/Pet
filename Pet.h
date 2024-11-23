#ifndef PET_H
#define PET_H

#include "Character.h"

class Pet : public Character
{
public:
    Pet();
    void onUpdate(float delta) override;
    void onRender() override;
protected:
};

#endif // PET_H
