#include "Knight.h"
#include "SDL2/SDL.h"
#include <filesystem>
#include "../Graphics/TextureManager.h"
#include "../Inputs/Input.h"
#include "../Camera/Camera.h"
#include "../Collision/CollisionHandler.h"
#include "../Core/Log.h"
#include "../Factory/ObjectFactory.h"

static Registrar<Knight> registrar("Knight");

Knight::Knight(Properties* props) : Character(props)
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
    m_Collider->SetOffset(-40, -10, 80, 15);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new SequenceAnimation();
    std::string animationFilePath = std::filesystem::absolute("assets/animation.xml").string();
    CORE_WARN("Animation file path: {0}", animationFilePath);
    m_Animation->Parse(animationFilePath);
}

void Knight::Draw()
{
    m_Animation->DrawFrame(m_Transform->X, m_Transform->Y, 1.0f, 1.0f, m_Flip);
    m_Collider->Draw();   
}

void Knight::Update(float deltatime)
{
    m_IsRunning = false;
    m_Animation->SetCurrentSequence("HeroKnight_Idle");
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

    ///////////////FALL detection//////////////////////////////////////////////////
    m_IsFalling = (m_RigidBody->GetVelocity().Y > 0 && !m_IsGrounded);
    ///////////////////////////////////////////////////////////////////////////////


    // move on x-axis
    m_RigidBody->Update(deltatime);
    m_LastSafePosition.X = m_Transform->X;
    m_Transform->X += (m_RigidBody->GetPosition().X);
    m_Collider->Set(m_Transform->X, m_Transform->Y, WIDTH, HEIGHT);

    if(m_Collider->CollideWithMap())
        m_Transform->X = m_LastSafePosition.X;

    // move on y-axis
    m_RigidBody->Update(deltatime);
    m_LastSafePosition.Y = m_Transform->Y;
    m_Transform->Y += (m_RigidBody->GetPosition().Y);
    m_Collider->Set(m_Transform->X, m_Transform->Y, WIDTH, HEIGHT);

    if(m_Collider->CollideWithMap())
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
    m_Animation->Update(deltatime);
}

void Knight::AnimationState()
{
    m_Animation->SetCurrentSequence("HeroKnight_Idle");

    if(m_IsRunning)
        m_Animation->SetCurrentSequence("HeroKnight_Run");
    
    if(m_IsJumping)
        m_Animation->SetCurrentSequence("HeroKnight_Jump");
    
    if(m_IsFalling)
        m_Animation->SetCurrentSequence("HeroKnight_Fall");
    
    if(m_IsAttacking)
        m_Animation->SetCurrentSequence("HeroKnight_Attack1");

}

void Knight::Clean()
{
    delete m_Collider;
    delete m_RigidBody;
    delete m_Animation;
}

