#ifndef WARIOR_H
#define WARIOR_H

#include "Character.h"
#include "../Animation/Animation.h"

class Warrior : public Character
{
    public:
        Warrior(Properties* props);
        
        virtual void Draw();
        virtual void Update(float deltatime);
        virtual void Clean();

    private:
        int m_Row, m_Frame, m_FrameCount;
        int m_AnimSpeed;

        Animation* m_Animation;
};

#endif