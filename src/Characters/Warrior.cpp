#include "Warrior.h"
#include "../Graphics/TextureManager.h"
#include "SDL2/SDL.h"
#include "../Inputs/Input.h"


Warrior::Warrior(Properties* props) : Character(props)
{

    m_RigidBody = new RigidBody();

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 8, 120, SDL_FLIP_NONE);
}

void Warrior::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Warrior::Update(float deltatime)
{
    m_Animation->SetProps("player_idle", 0, 4, 100, SDL_FLIP_NONE);
    m_RigidBody->UnSetForce();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT))
    {
        m_RigidBody->ApplyForceX(WARRIOR_SPEED * FORWARD);
        m_Animation->SetProps("player_walk", 0, 8, 100, SDL_FLIP_NONE);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFT))
    {
        m_RigidBody->ApplyForceX(WARRIOR_SPEED * BACKWARD);
        m_Animation->SetProps("player_walk", 0, 8, 100, SDL_FLIP_HORIZONTAL);
    }

    m_RigidBody->Update(deltatime);
    m_Transform->TranslateX(m_RigidBody->GetPosition().X);
    //m_Transform->TranslateY(m_RigidBody->GetPosition().Y);

    m_Animation->Update();
}

void Warrior::Clean()
{
    TextureManager::GetInstance()->Clean();
}

