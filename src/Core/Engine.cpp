#include "Engine.h"
#include <cassert>
#include "../Inputs/Input.h"
#include "../States/StateManager.h"
#include "../States/Play.h"
#include "Log.h"

// ImGui includes are already in the header

Engine* Engine::s_Instance = nullptr;

bool Engine::Init() {
    Log::Init();

    // Initialize SDL and create window
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        SDL_Log("Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if (m_Window == nullptr) {
        SDL_Log("Could not create window: %s\n", SDL_GetError());
        return false;
    }

    // Create renderer
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == nullptr) {
        SDL_Log("Could not create renderer: %s\n", SDL_GetError());
        return false;
    }

    SetWidth(SCREEN_WIDTH);
    SetHeight(SCREEN_HEIGHT);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(m_Window, m_Renderer);
    ImGui_ImplSDLRenderer2_Init(m_Renderer);

    StateManager::GetInstance()->ChangeState(new Play());
    m_IsRunning = true;
    return true;
}

void Engine::Render() {
        
   
    // SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
    // SDL_RenderClear(m_Renderer);
   
    //SDL_RenderPresent(m_Renderer);
}

void Engine::Update() {
    // Update your game logic here
}

void Engine::Events() {
}

bool Engine::Clean() {
    
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();

    return true;
}

void Engine::Quit() {
    m_IsRunning = false;
}
