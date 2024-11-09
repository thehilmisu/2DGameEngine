#ifndef WARIOR_H
#define WARIOR_H

#include "Character.h"
#include "../Animation/Animation.h"
#include "../Physics/RigidBody.h"

class Warrior : public Character
{
    public:
        Warrior(Properties* props);
        
        virtual void Draw();
        virtual void Update(float deltatime);
        virtual void Clean();

    private:
        Animation* m_Animation;
        RigidBody* m_RigidBody;
};

#endif