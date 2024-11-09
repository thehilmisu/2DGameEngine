#ifndef IOBJECT_H
#define IOBJECT_H

class IObject
{
    public:
        virtual void Draw() = 0;
        virtual void Update(float deltatime) = 0;
        virtual void Clean() = 0;
};

#endif