#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Object/GameObject.h"
#include <string>

#define JUMP_FORCE 10.0f
#define JUMP_TIME 15.0f;

#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f

class Character: public GameObject {

    public:
        Character(Properties* props):GameObject(props){}
        virtual void Draw()=0;
        virtual void Clean()=0;
        virtual void Update(float dt)=0;

    protected:
        std::string m_Name;
};

#endif // CHARACTER_H
