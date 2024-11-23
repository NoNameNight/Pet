#include "CharacterManager.h"
#include "Pet.h"

CharacterManager *CharacterManager::instance()
{
    static CharacterManager manager;
    return &manager;
}

void CharacterManager::onUpdate(float delta)
{
    m_pet->onUpdate(delta);
}

void CharacterManager::onRender()
{
    m_pet->onRender();
}

CharacterManager::CharacterManager()
{

    m_pet = new Pet();

}

CharacterManager::~CharacterManager()
{
    if(!m_pet)
    {
        delete m_pet;
        m_pet = nullptr;
    }

}

