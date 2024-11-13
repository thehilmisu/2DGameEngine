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
    m_Animation->SetProps(m_TextureID, 0, 8, ANIMATION_SPEED, SDL_FLIP_NONE);

}

Knight::Knight() : Character(new Properties("HeroKnight_Idle_0", 200, 200, WIDTH, HEIGHT))
{
    m_JumpTime = JUMP_TIME;
    m_JumpForce = JUMP_FORCE;

    m_Collider = new Collider();
    m_Collider->SetOffset(0, 0, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new Animation();

    TextureManager::GetInstance()->Load("HeroKnight_Idle_0", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Idle/HeroKnight_Idle_0.png");
    TextureManager::GetInstance()->Load("HeroKnight_Idle_1", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Idle/HeroKnight_Idle_1.png");
    TextureManager::GetInstance()->Load("HeroKnight_Idle_2", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Idle/HeroKnight_Idle_2.png");
    TextureManager::GetInstance()->Load("HeroKnight_Idle_3", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Idle/HeroKnight_Idle_3.png");
    TextureManager::GetInstance()->Load("HeroKnight_Idle_4", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Idle/HeroKnight_Idle_4.png");
    TextureManager::GetInstance()->Load("HeroKnight_Idle_5", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Idle/HeroKnight_Idle_5.png");
    TextureManager::GetInstance()->Load("HeroKnight_Idle_6", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Idle/HeroKnight_Idle_6.png");
    TextureManager::GetInstance()->Load("HeroKnight_Idle_7", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Idle/HeroKnight_Idle_7.png");

    for(int i =0; i < 8; i++)
        m_IdleTextureIDs.push_back("HeroKnight_Idle_" + std::to_string(i));

    TextureManager::GetInstance()->Load("HeroKnight_Run_0", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Run/HeroKnight_Run_0.png");
    TextureManager::GetInstance()->Load("HeroKnight_Run_1", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Run/HeroKnight_Run_1.png");
    TextureManager::GetInstance()->Load("HeroKnight_Run_2", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Run/HeroKnight_Run_2.png");
    TextureManager::GetInstance()->Load("HeroKnight_Run_3", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Run/HeroKnight_Run_3.png");
    TextureManager::GetInstance()->Load("HeroKnight_Run_4", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Run/HeroKnight_Run_4.png");
    TextureManager::GetInstance()->Load("HeroKnight_Run_5", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Run/HeroKnight_Run_5.png");
    TextureManager::GetInstance()->Load("HeroKnight_Run_6", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Run/HeroKnight_Run_6.png");
    TextureManager::GetInstance()->Load("HeroKnight_Run_7", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Run/HeroKnight_Run_7.png");
    TextureManager::GetInstance()->Load("HeroKnight_Run_8", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Run/HeroKnight_Run_8.png");
    TextureManager::GetInstance()->Load("HeroKnight_Run_9", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Run/HeroKnight_Run_9.png");

    for(int i =0; i < 10; i++)
        m_RunTextureIDs.push_back("HeroKnight_Run_" + std::to_string(i));

    TextureManager::GetInstance()->Load("HeroKnight_Jump_0", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Jump/HeroKnight_Jump_0.png");
    TextureManager::GetInstance()->Load("HeroKnight_Jump_1", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Jump/HeroKnight_Jump_1.png");
    TextureManager::GetInstance()->Load("HeroKnight_Jump_2", "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/HeroKnight/Jump/HeroKnight_Jump_2.png");

    for(int i =0; i < 3; i++)
        m_JumpTextureIDs.push_back("HeroKnight_Jump_" + std::to_string(i));



}

void Knight::Draw()
{
    m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

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

    m_Animation->SetProps(m_IdleTextureIDs, ANIMATION_SPEED, SDL_FLIP_NONE);
    m_RigidBody->UnSetForce();

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_RIGHT))
    {
        m_RigidBody->ApplyForceX(KNIGHT_SPEED * FORWARD);
        m_Animation->SetProps(m_RunTextureIDs, ANIMATION_SPEED, SDL_FLIP_NONE);
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_LEFT))
    {
        m_RigidBody->ApplyForceX(KNIGHT_SPEED * BACKWARD);
        m_Animation->SetProps(m_RunTextureIDs, ANIMATION_SPEED, SDL_FLIP_HORIZONTAL);
    }
    
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_IsGrounded)
    {
        m_IsJumping = true;
        m_IsGrounded = false;
        m_RigidBody->ApplyForceY(m_JumpForce * UPWARD);
        m_Animation->SetProps(m_JumpTextureIDs, ANIMATION_SPEED, SDL_FLIP_NONE); 
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

    m_Animation->Update();
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
}

