#include "Enemy.h"
#include "../Camera/Camera.h"
#include "../Collision/CollisionHandler.h"
#include <iostream>

static Registrar<Enemy> registrar("Enemy");

Enemy::Enemy(Transform* tf):GameObject(tf){

    m_RigiBody = new RigidBody();
    m_RigiBody->SetGravity(3.5);
    m_Collider = new Collider();

    m_Animation = new SeqAnimation(false);
    m_Animation->Parse("assets/animations/boss/boss.aml");
    m_Animation->SetCurrentSeq("boss_appear");
}

void Enemy::Draw(){
    //m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, m_Flip, 0.3f, 0.3f);
}

void Enemy::Update(float dt){

    // X-Axis movements
    m_RigiBody->Update(dt);
    m_LastSafePosition.X = m_Tf->X;
    m_Tf->X += m_RigiBody->GetPosition().X;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 140, 100);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Tf->X = m_LastSafePosition.X;

    // Y-Axis movements
    m_RigiBody->Update(dt);
    m_LastSafePosition.Y = m_Tf->Y;
    m_Tf->Y += m_RigiBody->GetPosition().Y;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 140, 100);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Tf->Y = m_LastSafePosition.Y;

    m_Animation->Update(dt);

    if(m_Animation->IsEnded()){
        m_Animation->SetRepeat(true);
        m_Animation->SetCurrentSeq("boss_idle");
    }
}


void Enemy::Clean(){

}



