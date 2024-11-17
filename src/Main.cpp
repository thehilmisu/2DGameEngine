
#include "Core/Engine.h"
#include "Timer/Timer.h"
#include "Inputs/Input.h"
#include "States/StateManager.h"

int main(int argc, char** argv)
{
    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunning())
    {
        Input::GetInstance()->Listen();
        StateManager::GetInstance()->Render();
        StateManager::GetInstance()->Update();        
        Timer::GetInstance()->Tick();
    }

    Engine::GetInstance()->Clean();
   
    return 0;
}