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
    delete m_pet;
}

