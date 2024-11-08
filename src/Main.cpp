
#include "Core/Engine.h"

int main(int argc, char** argv)
{
    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunnning())
    {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update();
        Engine::GetInstance()->Render();
    }

    Engine::GetInstance()->Clean();
   
    return 0;
}