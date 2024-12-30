#include "Editor.h"
#include "../Core/Log.h"
#include "../Inputs/Input.h"
#include "Play.h"
#include "SDL_render.h"
#include "StateManager.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

Editor::Editor() {}

bool Editor::Init() {
  CORE_INFO("Editor initialized");
  return true;
}

void Editor::RenderBottomBar() {

    ImGui::SetNextWindowPos(ImVec2(200, Engine::GetInstance()->GetHeight() - 250));
    ImGui::SetNextWindowSize(ImVec2(Engine::GetInstance()->GetWidth() - 200, 250));
    ImGui::Begin("Bottombar", nullptr,
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);


    if(ImGui::BeginTable("BottomLogTable", 3)){

        ImGui::TableSetupColumn("Time stamp", ImGuiTableColumnFlags_WidthFixed, 200.0f);
        ImGui::TableSetupColumn("Provider", ImGuiTableColumnFlags_WidthFixed, 200.0f);
        ImGui::TableSetupColumn("Log", ImGuiTableColumnFlags_WidthFixed, Engine::GetInstance()->GetWidth() - 600.0f);
        ImGui::TableHeadersRow();

        //add elements to table
        for(int row = 0; row < 10; row++){
            ImGui::TableNextRow();
            for(int col = 0; col < 3; col++){
                ImGui::TableSetColumnIndex(col);
                ImGui::Text("Row %d, Col %d", row, col);
            }
        }

        ImGui::EndTable();
    }
    ImGui::End();
}

void Editor::RenderTopBar() {

    float btn_w = 100.0f;
    float btn_h = 20.0f;
    float w = Engine::GetInstance()->GetWidth() - 200;
    float h = 50.0f;
    float total_btn_w = (btn_w * 3);
    float spacing = 10.0f;
    float offset = (w - total_btn_w) / 2.0f;
    
    ImGui::SetNextWindowPos(ImVec2(200, 0));
    ImGui::SetNextWindowSize(ImVec2(w, h));
    ImGui::Begin("Topbar", nullptr,
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);


    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + offset, 15.0f));
    if (ImGui::Button("Play", ImVec2(btn_w, btn_h))) {
        // StartGame();
    }
    
    ImGui::SameLine();
    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + spacing, 15.0f));
    if (ImGui::Button("Pause", ImVec2(btn_w, btn_h))) {
        CORE_INFO("Settings Button");
    }
    
    ImGui::SameLine();
    ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + spacing, 15.0f));
    if (ImGui::Button("Stop", ImVec2(btn_w, btn_h))) {
        CORE_INFO("Another Button");
    }

    ImGui::End();
}

void Editor::RenderSideBar() {
  
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(200, Engine::GetInstance()->GetHeight()));
    ImGui::Begin("Sidebar", nullptr,
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);


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

    ImGui::End();
}
void Editor::Render() {

  ImGuiIO& io = ImGui::GetIO();
  io.DisplaySize = ImVec2(Engine::GetInstance()->GetWidth(), Engine::GetInstance()->GetHeight());
  // Start the ImGui frame
  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();


  RenderSideBar();
  RenderTopBar();
  RenderBottomBar();

  ImGui::Render();
  ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(),
                                        Engine::GetInstance()->GetRenderer());
}
