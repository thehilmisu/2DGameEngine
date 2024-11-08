#include "Engine.h"
#include "Log.h"


Engine* Engine::s_Instance = nullptr;

bool Engine::Init()
{
    Log::Init();

    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        CORE_ERROR("Failed to initialize SDL: {0}", SDL_GetError());
        return false;
    }

    CORE_INFO("SDL Initialized successfully");

    return m_IsRunning = true;
}

bool Engine::Clean()
{
    return true;
}

void Engine::Quit()
{

}

void Engine::Update()
{
    CORE_INFO("Updating...");
}

void Engine::Render()
{

}

void Engine::Events()
{

}