#ifndef KNIGHT_H
#define KNIGHT_H

#include "Character.h"
#include "../Animation/Animation.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Collider.h"
#include "../Physics/Vector2D.h"
#include <vector>
#include <string>

#define KNIGHT_SPEED    5.0f
#define JUMP_TIME       15.0f
#define JUMP_FORCE      10.0f

#define ANIMATION_SPEED 100
#define WIDTH           100
#define HEIGHT          55

class Knight : public Character
{
    public:
        Knight(Properties* props);
        Knight();
        
        virtual void Draw();
        virtual void Update(float deltatime);
        virtual void Clean();

    private:
        float m_IsJumping;
        float m_IsGrounded;
        float m_JumpTime;
        float m_JumpForce;

        Collider* m_Collider;
        Animation* m_Animation;
        RigidBody* m_RigidBody;

        Vector2D m_LastSafePosition;

        std::vector<std::string> m_IdleTextureIDs;
        std::vector<std::string> m_RunTextureIDs;
        std::vector<std::string> m_JumpTextureIDs;
        std::vector<std::string> m_Attack1TextureIDs;
};

#endif