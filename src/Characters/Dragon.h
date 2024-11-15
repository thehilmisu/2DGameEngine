#ifndef DRAGON_H
#define DRAGON_H

#include "Character.h"

#include "../Animation/SpriteAnimation.h"
#include "../Physics/RigidBody.h"
#include "../Physics/Collider.h"
#include "../Physics/Vector2D.h"

class Dragon : public Character 
{
public:
    Dragon(Properties* props);
    
    virtual void Draw();
    virtual void Clean();
    virtual void Update(float deltatime);

private:
    Collider* m_Collider;
    RigidBody* m_RigidBody;
    SpriteAnimation* m_Animation;
    Vector2D m_LastSafePosition;
};

#endif // Dragon