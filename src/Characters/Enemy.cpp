#include "Enemy.h"
#include "../Collision/CollisionHandler.h"
#include "../Camera/Camera.h"
#include "../Core/Log.h"

Enemy::Enemy(Properties* props) : Character(props) 
{
    m_Collider = new Collider();
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.5f);
    
    
    m_Animation = new SequenceAnimation(false);
    m_Animation->Parse("assets/animation.xml");
    m_Animation->SetCurrentSequence("Enemy_Idle");
    
}

void Enemy::Draw() 
{
    m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);
}

void Enemy::Clean() 
{
    delete m_Collider;
    delete m_RigidBody;
    delete m_Animation;
}

void Enemy::Update(float deltatime) 
{
    // move on x-axis
    m_RigidBody->Update(deltatime);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->TranslateX(m_RigidBody->GetPosition().X);
    m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->X = m_LastSafePosition.X;
    
   

    // move on y-axis
    m_RigidBody->Update(deltatime);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
    m_Collider->Set(m_Transform->X, m_Transform->Y, m_Width, m_Height);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->Y = m_LastSafePosition.Y;


    m_Animation->Update(deltatime);

    if (m_Animation->IsEnded())
    {
        m_Animation->SetRepeat(true);
        m_Animation->SetCurrentSequence("Enemy_Idle");
    }

    m_Animation->Update(deltatime);
}