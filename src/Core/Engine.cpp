#include "Engine.h"
#include "Log.h"
#include "../Graphics/TextureManager.h"
#include "../Physics/Transform.h"
#include "../Inputs/Input.h"
#include "../Characters/Knight.h"
#include "../Timer/Timer.h"
#include "../Map/MapParser.h"
#include "../Camera/Camera.h"
#include "../Characters/Enemy.h"
#include "../Characters/Dragon.h"

Engine* Engine::s_Instance = nullptr;
Knight* knight = nullptr;
Enemy* enemy = nullptr;
Dragon* dragon = nullptr;

bool Engine::Init()
{
    Log::Init();

    if(SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        CORE_ERROR("Failed to initialize SDL: {0}", SDL_GetError());
        return false;
    }

    CORE_INFO("SDL Initialized successfully");

    m_Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(m_Window == nullptr)
    {
        CORE_ERROR("Failed to Create Window: {0}", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(m_Renderer == nullptr)
    {
        CORE_ERROR("Failed to Create Renderer: {0}", SDL_GetError());
        return false;
    }

    if(!MapParser::GetInstance()->Load())
    {
        CORE_ERROR("Failed to load the map");
    }

    m_LevelMap = MapParser::GetInstance()->GetMap("map");


    TextureManager::GetInstance()->ParseTextures("assets/textures.xml");

    knight = new Knight();
    enemy = new Enemy(new Properties("Enemy_Idle", 280, 200, 64, 64, SDL_FLIP_HORIZONTAL));
    dragon = new Dragon(new Properties("Dragon", 500, 200, 72, 72, SDL_FLIP_HORIZONTAL));

    m_GameObjects.push_back(knight);
    m_GameObjects.push_back(enemy);
    m_GameObjects.push_back(dragon);

    Camera::GetInstance()->SetTarget(knight->GetOrigin());

    return m_IsRunning = true;
}

void Engine::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();
    m_LevelMap->Update();

    for(size_t i = 0; i < m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->Update(dt);
    }

    Camera::GetInstance()->Update(dt);    
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);

    TextureManager::GetInstance()->Draw("background", 0, 0, 2560, 640, 1.0f,1.0f, 0.4f, SDL_FLIP_NONE);
    m_LevelMap->Render();

    for(size_t i = 0; i < m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->Draw();
    }

    SDL_RenderPresent(m_Renderer);
}

void Engine::Events()
{
    Input::GetInstance()->Listen();
}


bool Engine::Clean()
{
    for(size_t i = 0; i < m_GameObjects.size(); i++)
    {
        m_GameObjects[i]->Clean();
    }
    
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();

    return true;
}

void Engine::Quit()
{
    m_IsRunning = false;
}   