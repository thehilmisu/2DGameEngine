#ifndef ANIMATION_H
#define ANIMATION_H


class Animation
{
    public:
        Animation(bool repeat = true) : m_Repeat(repeat){ m_IsEnded = false; }
        virtual ~Animation() = default;
        virtual void Update(float deltatime) = 0;
        inline bool IsEnded() { return m_IsEnded; }

    protected:
        bool m_Repeat;
        bool m_IsEnded;
        int m_CurrentFrame;
};  

#endif