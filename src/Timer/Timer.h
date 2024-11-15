#ifndef TIMER_H
#define TIMER_H

const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer
{
    public:
        void Tick();
        inline float GetDeltaTime() { return m_DeltaTime; }
        static Timer* GetInstance(){
                return s_Instance = ( s_Instance != nullptr) ? s_Instance : new Timer();
        }

    private:
        Timer(){};
        ~Timer() = default;
        static Timer* s_Instance;
        float m_DeltaTime;
        float m_LastTime;
};

#endif