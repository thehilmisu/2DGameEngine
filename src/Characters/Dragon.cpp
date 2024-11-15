#include "Dragon.h"
#include "../Collision/CollisionHandler.h"
#include "../Camera/Camera.h"
#include "../Core/Log.h"

Dragon::Dragon(Properties* props) : Character(props) 
{
    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(1.0f);
    
    m_Collider = new Collider();
    //m_Collider->SetOffset(-20, -5, 40, 15);
    
    m_Animation = new SpriteAnimation();
    m_Animation->SetProps("Dragon", 0, 24, 100);
    
}

void Dragon::Draw() 
{
    m_Animation->Draw("Dragon",m_Transform->X, m_Transform->Y, 72, 72, m_Flip);

    //TODO: remove here and add it to collider, to see the box collider
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;  
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
    //////////////////////////////////////////////////////////
}

void Dragon::Clean() 
{
    delete m_Collider;
    delete m_RigidBody;
    delete m_Animation;
}

void Dragon::Update(float deltatime) 
{
    // move on x-axis
    m_RigidBody->Update(deltatime);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->TranslateX(m_RigidBody->GetPosition().X);
    m_Collider->Set(m_Transform->X, m_Transform->Y, 64, 64);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->X = m_LastSafePosition.X;
    

    // move on y-axis
    m_RigidBody->Update(deltatime);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->TranslateY(m_RigidBody->GetPosition().Y);
    m_Collider->Set(m_Transform->X, m_Transform->Y, 64, 64);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->Y = m_LastSafePosition.Y;


    // if(m_Animation->IsEnded())
    //     m_Animation->SetProps("Enemy_Idle", 0, 7, 100);

    //update the current value of origin
    m_origin->x = m_Transform->X + m_Width / 2;
    m_origin->y = m_Transform->Y + m_Height / 2;
    
    m_Animation->Update(deltatime);
}