#include "StateManager.h"

StateManager* StateManager::s_Instance = nullptr;

void StateManager::PopState(){
    SDL_Delay(100);
    if(m_GameStates.size() > 1){
        if(m_GameStates.back()->Exit()){
            delete m_GameStates.back();
            m_GameStates.pop_back();
        }
    }
}

void StateManager::PushState(GameState* current){
    SDL_Delay(100);
    m_GameStates.push_back(current);
    m_GameStates.back()->Init();
}

void StateManager::ChangeState(GameState* target){
    SDL_Delay(100);
    if(!m_GameStates.empty()){
        if(m_GameStates.back()->Exit()){
            delete m_GameStates.back();
            m_GameStates.pop_back();
        }
    }
    m_GameStates.push_back(target);
    m_GameStates.back()->Init();
}

void StateManager::Render(){
    m_GameStates.back()->Render();
}

void StateManager::Update(){
    m_GameStates.back()->Update();
}

void StateManager::Clean(){

    for(auto state : m_GameStates){
        state->Exit();
        delete state;
    }

    m_GameStates.clear();
}