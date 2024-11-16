#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"
#include "../Animation/SpriteAnimation.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Collider.h"
#include "../Physics/Vector2D.h"

class Warrior: public Character{

    public:
        Warrior(Properties* props);
        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);

    private:
        void AnimationState();

    private:
        bool m_IsRunning;
        bool m_IsJumping;
        bool m_IsFalling;
        bool m_IsGrounded;
        bool m_IsAttacking;
        bool m_IsCrouching;

        float m_JumpTime;
        float m_JumpForce;
        float m_AttackTime;

        Collider* m_Collider;
        SpriteAnimation* m_Animation;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
};

#endif // WARRIOR_H
