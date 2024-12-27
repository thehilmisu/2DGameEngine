#include "Menu.h"
#include "../Core/Log.h"
#include "../Inputs/Input.h"
#include "Play.h"
#include "SDL_render.h"
#include "StateManager.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

Menu::Menu() {}

bool Menu::Init() {
  m_Ctxt = Engine::GetInstance()->GetRenderer();
  CORE_INFO("Menu initialized");
  return true;
}

void Menu::RenderTopBar() {

  ImGui::SetNextWindowPos(ImVec2(200, 0));
  ImGui::SetNextWindowSize(ImVec2(-1, 50));
  ImGui::BeginChild("Topbar", ImVec2(-1, 50), true);
  ImGui::Text("Top Bar");

  if (ImGui::Button("Play Mode", ImVec2(100, 20))) {
    CORE_INFO("Play Mode Button");
    std::cout << "Play" << std::endl;
  }
  ImGui::SameLine();
  if (ImGui::Button("Settings", ImVec2(100, 20))) {
    CORE_INFO("Settings Button");
  }
  ImGui::SameLine();
  if (ImGui::Button("Another Button", ImVec2(100, 20))) {
    CORE_INFO("Another Button");
  }

  ImGui::EndChild();
}

void Menu::RenderSideBar() {
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSize(ImVec2(200, -1));
  ImGui::BeginChild("Sidebar", ImVec2(200, 0), true);
  ImGui::Text("Sidebar");

  // setting x or y as -1 means, it will fill the space
  if (ImGui::Button("Play Mode", ImVec2(-1, 0))) {
    CORE_INFO("Play Mode Button");
  }
  if (ImGui::Button("Settings", ImVec2(-1, 0))) {
    CORE_INFO("Settings Button");
  }
  if (ImGui::Button("Another Button", ImVec2(-1, 0))) {
    CORE_INFO("Another Button");
  }

  ImGui::EndChild();
}
void Menu::Render() {

  // Start the ImGui frame
  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();

  // ImGui Menu window
  ImGui::Begin("HknGameEngine!", nullptr,
               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                   ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

  RenderSideBar();
  RenderTopBar();

  ImGui::End();
  ImGui::Render();

  SDL_SetRenderDrawColor(m_Ctxt, 16, 45, 70, 255);
  SDL_RenderClear(m_Ctxt);

  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(),
                                        Engine::GetInstance()->GetRenderer());

  // The area between the side bar and top bar
  SDL_SetRenderDrawColor(m_Ctxt, 70, 45, 16, 255);
  SDL_Rect emptyArea = {200, 50, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 50};
  SDL_RenderFillRect(m_Ctxt, &emptyArea);

  SDL_RenderPresent(m_Ctxt);
}

void Menu::Update() {
  // frame1->Update();
}

bool Menu::Exit() {
  CORE_INFO("Menu exited");
  return true;
}

// change between states
void Menu::StartGame() { StateManager::GetInstance()->ChangeState(new Play()); }

void Menu::Editor() { std::cout << "editor mode\n"; }

void Menu::Settings() { std::cout << "options mode\n"; }

void Menu::Quit() { std::cout << "quit game\n"; }
