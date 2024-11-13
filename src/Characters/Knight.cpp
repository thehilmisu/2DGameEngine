#include "Knight.h"
#include "SDL2/SDL.h"
#include "../Graphics/TextureManager.h"
#include "../Inputs/Input.h"
#include "../Camera/Camera.h"
#include "../Collision/CollisionHandler.h"


Knight::Knight(Properties* props) : Character(props)
{

    m_RigidBody = new RigidBody();

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 0, 8, ANIMATION_SPEED);

}

Knight::Knight() : Character(new Properties("HeroKnight_Idle_0", 200, 200, WIDTH, HEIGHT))
{
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;
    m_AttackTime = ATTACK_TIME;

    m_IsRunning = false;
    m_IsJumping =false;
    m_IsFalling =false;
    m_IsGrounded =false;
    m_IsAttacking =false;


    m_Collider = new Collider();
    m_Collider->SetOffset(0, 0, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new Animation();

    // TODO: get those frame counts from xml 
    const int idle_frame_count =8;
    for(int i =0; i < idle_frame_count; i++)
        m_IdleTextureIDs.push_back("HeroKnight_Idle_" + std::to_string(i));

    const int running_frame_count = 10;
    for(int i =0; i < running_frame_count; i++)
        m_RunTextureIDs.push_back("HeroKnight_Run_" + std::to_string(i));

    const int jumping_frame_count = 3;
    for(int i =0; i < jumping_frame_count; i++)
        m_JumpTextureIDs.push_back("HeroKnight_Jump_" + std::to_string(i));

    const int fall_frame_count = 4;
    for(int i =0; i < fall_frame_count; i++)
        m_FallTextureIDs.push_back("HeroKnight_Fall_" + std::to_string(i));
   
    const int attack1_frame_count = 5;
    for(int i =0; i < attack1_frame_count; i++)
        m_Attack1TextureIDs.push_back("HeroKnight_Attack1_" + std::to_string(i));


}

void Knight::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height, m_Flip);

    //TODO: remove here and add it to collider, to see the box collider
    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_Collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;  
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
    //////////////////////////////////////////////////////////
}

void Knight::Update(float deltatime)
{
    m_IsRunning = false;
    m_Animation->SetProps(m_IdleTextureIDs, ANIMATION_SPEED);
    m_RigidBody->UnSetForce();

    /////////////////////MOVEMENT//////////////////////////////////////////////////
    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_IsAttacking)
    {
        m_RigidBody->ApplyForceX(FORWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_NONE;
        m_IsRunning = true;
    }

    if(Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_IsAttacking)
    {
        m_RigidBody->ApplyForceX(BACKWARD * RUN_FORCE);
        m_Flip = SDL_FLIP_HORIZONTAL;
        m_IsRunning = true;
    }
    ///////////////////////////////////////////////////////////////////////////////

    /////////////////////ATTACK////////////////////////////////////////////////////
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RCTRL))
    {
        m_RigidBody->UnSetForce();
        m_IsAttacking = true;
    }

    if(m_IsAttacking && m_AttackTime > 0)
    {
        m_AttackTime -= deltatime;
    }
    else
    {
        m_IsAttacking = false;
        m_AttackTime = ATTACK_TIME;
    }
    ///////////////////////////////////////////////////////////////////////////////

    ////////////////////JUMP///////////////////////////////////////////////////////
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded)
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(m_JumpForce * UPWARD);
    }
    
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsJumping && m_JumpTime > 0)
    {
        m_JumpTime -= deltatime;
        m_RigidBody->ApplyForceY(m_JumpForce * UPWARD);
    }
    else
    {
        m_IsJumping = false;
        m_JumpTime = JUMP_TIME;
    }
    ///////////////////////////////////////////////////////////////////////////////

    ///////////////FALL////////////////////////////////////////////////////////////
    if(m_RigidBody->GetVelocity().Y > 0 && !m_IsGrounded)
        m_IsFalling = true;
    else
        m_IsFalling = false;
    ///////////////////////////////////////////////////////////////////////////////


    // move on x-axis
    m_RigidBody->Update(deltatime);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += (m_RigidBody->GetPosition().X);
    m_Collider->Set(m_Transform->X, m_Transform->Y, WIDTH, HEIGHT);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
        m_Transform->X = m_LastSafePosition.X;

    // move on y-axis
    m_RigidBody->Update(deltatime);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += (m_RigidBody->GetPosition().Y);
    m_Collider->Set(m_Transform->X, m_Transform->Y, WIDTH, HEIGHT);

    if(CollisionHandler::GetInstance()->MapCollision(m_Collider->Get()))
    {
        m_IsGrounded = true;
        m_Transform->Y = m_LastSafePosition.Y;
    }
    else
    {
        m_IsGrounded = false;
    }

    //update the current value of origin
    m_origin->x = m_Transform->X + m_Width / 2;
    m_origin->y = m_Transform->Y + m_Height / 2;

    AnimationState();
    m_Animation->Update();
}

void Knight::AnimationState()
{
    m_Animation->SetProps(m_IdleTextureIDs, ANIMATION_SPEED);

    if(m_IsRunning)
        m_Animation->SetProps(m_RunTextureIDs, ANIMATION_SPEED);
    
    if(m_IsJumping)
        m_Animation->SetProps(m_JumpTextureIDs, ANIMATION_SPEED); 
    
    if(m_IsFalling)
        m_Animation->SetProps(m_FallTextureIDs, ANIMATION_SPEED); 
    
    if(m_IsAttacking)
        m_Animation->SetProps(m_Attack1TextureIDs, ANIMATION_SPEED); 

}

void Knight::Clean()
{
    for(const auto& id : m_IdleTextureIDs)
        TextureManager::GetInstance()->Drop(id);
    m_IdleTextureIDs.clear();

    for(const auto& id : m_RunTextureIDs)
        TextureManager::GetInstance()->Drop(id);
    m_RunTextureIDs.clear();

    for(const auto& id : m_JumpTextureIDs)
        TextureManager::GetInstance()->Drop(id);
    m_JumpTextureIDs.clear();

    for(const auto& id : m_Attack1TextureIDs)
        TextureManager::GetInstance()->Drop(id);
    m_Attack1TextureIDs.clear();

    for(const auto& id : m_FallTextureIDs)
        TextureManager::GetInstance()->Drop(id);
    m_FallTextureIDs.clear();
}

