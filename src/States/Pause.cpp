#include "Pause.h"
#include "Play.h"
#include "../Inputs/Input.h"
#include "StateManager.h"

#include "../Core/Log.h"

Pause::Pause(){

}

bool Pause::Init(){
    m_Ctxt = Engine::GetInstance()->GetRenderer();
    // frame2 = new Gui::Frame(Gui::Attr(m_Ctxt, 100, 100, 250, 100));
    // Gui::Button* btn = new Gui::Button(Gui::Attr(m_Ctxt, 50, 50, 100, 35), Resume);
    // frame2->AddChild(btn);
    CORE_INFO("Pause initialized");
    return true;
}

void Pause::Render(){
    SDL_SetRenderDrawColor(m_Ctxt, 211, 87, 85, 255);
    SDL_RenderClear(m_Ctxt);

    //frame2->Draw();
    SDL_RenderPresent(m_Ctxt);
}

void Pause::Update(){
    //frame2->Update();
}

bool Pause::Exit(){
    CORE_INFO("Pause exited");
    return true;
}

// Callbacks
void Pause::Resume(){
    StateManager::GetInstance()->PopState();
    CORE_INFO("Resume clicked");
}


