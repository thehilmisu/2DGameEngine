#include "Engine.h"
#include "assert.h"
#include "../Inputs/Input.h"
#include "../States/Menu.h"
#include "../States/Play.h"
#include "Log.h"

Engine* Engine::s_Instance = nullptr;

bool Engine::Init(){

    Log::Init();
    
    // initialize SDL and create window
    assert(SDL_Init(SDL_INIT_VIDEO)==0 && SDL_GetError());
    SDL_WindowFlags w_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, w_flags);
    assert(m_Window != nullptr && SDL_GetError());

    // create renderer context
    SDL_RendererFlags r_flags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    m_Renderer = SDL_CreateRenderer(m_Window, -1, r_flags);
    assert(m_Renderer != nullptr && SDL_GetError());

    ChangeState(new Play());
    return m_IsRunning = true;
}

void Engine::Render(){
   m_States.back()->Render();
}

void Engine::Update(){
     m_States.back()->Update();
}

void Engine::Events(){
    Input::GetInstance()->Listen();
}

bool Engine::Clean(){

    for(auto state : m_States){
        state->Exit();
        delete state;
    }
    m_States.clear();

    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit(){
    m_IsRunning = false;
}

void Engine::PopState(){
    SDL_Delay(100);
    if(m_States.size() > 1){
        if(m_States.back()->Exit()){
            delete m_States.back();
            m_States.pop_back();
        }
    }
}

void Engine::ChangeState(GameState* target){
    SDL_Delay(100);
    if(!m_States.empty()){
        if(m_States.back()->Exit()){
            delete m_States.back();
            m_States.pop_back();
        }
    }
    m_States.push_back(target);
    m_States.back()->Init();
}

void Engine::PushState(GameState* current){
    SDL_Delay(100);
    m_States.push_back(current);
    m_States.back()->Init();
}
