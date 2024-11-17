#include "Menu.h"
#include "Play.h"
#include "../Inputs/Input.h"
#include "../Core/Log.h"
#include "StateManager.h"

//Gui::Frame* frame1 = nullptr;

Menu::Menu(){}

bool Menu::Init(){
    m_Ctxt = Engine::GetInstance()->GetRenderer();
    
    // frame1 = new Gui::Frame(Gui::Attr(m_Ctxt, 100, 100, 250, 100));
    // Gui::Button* btn = new Gui::Button(Gui::Attr(m_Ctxt, 50, 50, 100, 35), StartGame);
    // frame1->AddChild(btn);

    CORE_INFO("Menu initialized");
    return true;
}

void Menu::Render(){
    SDL_SetRenderDrawColor(m_Ctxt, 16, 45, 70, 255);
    SDL_RenderClear(m_Ctxt);

    //frame1->Draw();

    SDL_RenderPresent(m_Ctxt);
}

void Menu::Update(){
    //frame1->Update();
}

bool Menu::Exit(){
    CORE_INFO("Menu exited");
    return true;
}

// Callbacks
void Menu::StartGame(){
    StateManager::GetInstance()->ChangeState(new Play());
}

void Menu::Editor(){
    std::cout << "editor mode\n";
}

void Menu::Settings(){
    std::cout << "options mode\n";
}

void Menu::Quit(){
    std::cout << "quit game\n";
}


