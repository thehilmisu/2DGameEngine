#include "Warrior.h"
#include "../Graphics/TextureManager.h"
#include "SDL2/SDL.h"


Warrior::Warrior(Properties* props) : Character(props)
{
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 4, 120, SDL_FLIP_NONE);
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float deltatime)
{
    m_Animation->Update();
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}

