#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H

#include "Character.h"



class CharacterManager
{
public:
    static CharacterManager* instance();

    Character* getPet()
    {
        return m_pet;
    }

    void onUpdate(float delta);
    void onRender();
private:
    Character* m_pet = nullptr;

private:
    CharacterManager();
    ~CharacterManager();
};


#endif // CHARACTERMANAGER_H
