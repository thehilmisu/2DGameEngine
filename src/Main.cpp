
#include "Core/Engine.h"
#include "Timer/Timer.h"

int main(int argc, char** argv)
{
    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunnning())
    {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();
   
    return 0;
}