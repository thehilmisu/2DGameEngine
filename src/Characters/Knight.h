#ifndef KNIGHT_H
#define KNIGHT_H

#include "Character.h"
#include "../Animation/SequenceAnimation.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Collider.h"
#include "../Physics/Vector2D.h"
#include <vector>
#include <string>

#define KNIGHT_SPEED    5.0f
#define JUMP_TIME       15.0f
#define JUMP_FORCE      10.0f
#define RUN_FORCE       4.0f
#define ATTACK_TIME     20.0f

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
        void AnimationState();

        float m_IsRunning;
        float m_IsJumping;
        float m_IsFalling;
        float m_IsGrounded;
        float m_IsAttacking;
        
        float m_JumpTime;
        float m_JumpForce;
        float m_AttackTime;

        Collider* m_Collider;
        SequenceAnimation* m_Animation;
        RigidBody* m_RigidBody;

        Vector2D m_LastSafePosition;
};

#endif