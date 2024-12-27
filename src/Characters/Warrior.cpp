#include "Warrior.h"
#include "../Graphics/TextureManager.h"
#include "SDL2/SDL.h"
#include "../Inputs/Input.h"
#include "../Core/Engine.h"
#include "../Collision/CollisionHandler.h"
#include "../Camera/Camera.h"
#include "../Factory/ObjectFactory.h"

static Registrar<Warrior> registrar("WARRIOR");

Warrior::Warrior(Transform* tf) : GameObject(tf){
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;

    m_Collider = new Collider();
    m_Collider->SetBuffer(-60, -26, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new SpriteAnimation();
    m_Animation->SetProps(1, 6, 100);
}

void Warrior::Draw(){
    //m_Collider->Draw();
    m_Animation->Draw(m_Tf);
}

void Warrior::Update(float dt){

    m_IsRunning = false;
    m_IsCrouching = false;
    m_RigidBody->UnSetForce();

    // Run forward
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking){
        m_RigidBody->ApplyForceX(FORWARD*RUN_FORCE);
        m_Tf->Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
    }

    // Run backward
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking){
        m_RigidBody->ApplyForceX(BACKWARD*RUN_FORCE);
        m_Tf->Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }

    // Crouch
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)){
        m_RigidBody->UnSetForce();
        m_IsCrouching = true;
    }

    // Attack
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_K)){
        m_RigidBody->UnSetForce();
        m_IsAttacking = true;
    }

    // Jump
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsGrounded){
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_IsJumping && m_JumpTime > 0){
        m_JumpTime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_JumpForce);
    }
    else{
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }

    // Fall
    if(m_RigidBody->GetVelocity().Y > 0 && !m_IsGrounded)
        m_IsFalling = true;
    else
        m_IsFalling = false;

    // Attack timer
    if(m_IsAttacking && m_AttackTime > 0){
        m_AttackTime -= dt;
    }
    else{
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }

    // move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_Tf->X;
    m_Tf->X += m_RigidBody->GetPosition().X;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 18, 50);

    if(m_Collider->CollideWithMap())
        m_Tf->X = m_LastSafePosition.X;


    // move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_Tf->Y;
    m_Tf->Y += m_RigidBody->GetPosition().Y;
    m_Collider->Set(m_Tf->X, m_Tf->Y, 18, 50);

    if(m_Collider->CollideWithMap()){
        m_IsGrounded = true;
        m_Tf->Y = m_LastSafePosition.Y;
    }
    else{
        m_IsGrounded = false;
    }

    m_Tf->Origin->X = m_Tf->X + m_Tf->Width/2.0f;
    m_Tf->Origin->Y = m_Tf->Y + m_Tf->Height/2.0f;

    AnimationState();
}


void Warrior::AnimationState(){
    // idling
    m_Tf->TextureID = "player_idle";
    m_Animation->SetProps(0, 6, 100);

    // running
    if(m_IsRunning){
        m_Tf->TextureID = "player_run";
        m_Animation->SetProps(0, 8, 80);
    }

    // crouching
    if(m_IsCrouching){
        m_Tf->TextureID = "player_crouch";
        m_Animation->SetProps(0, 6, 100);
    }

    // jumping
    if(m_IsJumping){
        m_Tf->TextureID = "player_jump";
        m_Animation->SetProps(0, 2, 200);
    }

    // falling
    if(m_IsFalling){
        m_Tf->TextureID = "player_fall";
        m_Animation->SetProps(0, 2, 400);
    }

    // attacking
    if(m_IsAttacking){
        m_Tf->TextureID = "player_attack";
        m_Animation->SetProps(0, 14, 80);
    }

    m_Animation->Update(0);
}

void Warrior::Clean(){

}

