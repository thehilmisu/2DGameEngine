#include "Engine.h"
#include "../Inputs/Input.h"
#include "../States/Menu.h"
#include "../States/Play.h"
#include "../States/StateManager.h"
#include "Log.h"
#include "SDL_events.h"
#include "SDL_render.h"
#include "assert.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

Engine *Engine::s_Instance = nullptr;

bool Engine::Init() {

  Log::Init();

  // initialize SDL and create window
  assert(SDL_Init(SDL_INIT_VIDEO) == 0 && SDL_GetError());
  SDL_WindowFlags w_flags =
      (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE |
                        SDL_WINDOW_ALLOW_HIGHDPI);
  m_Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, w_flags);
  assert(m_Window != nullptr && SDL_GetError());

  // create renderer context
  SDL_RendererFlags r_flags =
      (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  m_Renderer = SDL_CreateRenderer(m_Window, -1, r_flags);
  assert(m_Renderer != nullptr && SDL_GetError());

  SetWidth(SCREEN_WIDTH);
  SetHeight(SCREEN_HEIGHT);

  // Initialize ImGui
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(m_Window, m_Renderer);
  ImGui_ImplSDLRenderer2_Init(m_Renderer);

  StateManager::GetInstance()->ChangeState(new Menu());
  
  m_IsRunning = true;
  
  return true;
}

void Engine::Render() {
  // empty
}

void Engine::Update() {
  // empty
}

void Engine::Events(SDL_Event* event) {
 
    ImGui_ImplSDL2_ProcessEvent(event);
    
    if (event->window.event == SDL_WINDOWEVENT_RESIZED) {
        
        int width = event->window.data1;
        int height = event->window.data2;
        
        SetWidth(width);
        SetHeight(height);
        
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2((float)width, (float)height);
        CORE_WARN("Width : {0}, Height: {1}", width, height);

        SDL_RenderSetLogicalSize(m_Renderer, width, height);
        // ImGui_ImplSDLRenderer2_InvalidateDeviceObjects();
        ImGui_ImplSDLRenderer2_CreateDeviceObjects();
    }
}

bool Engine::Clean() {

  SDL_DestroyRenderer(m_Renderer);
  SDL_DestroyWindow(m_Window);
  IMG_Quit();
  SDL_Quit();

  return true;
}

void Engine::Quit() { m_IsRunning = false; }
