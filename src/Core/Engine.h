#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>

#include "../States/GameState.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Engine {

public:
  bool Init();
  bool Clean();
  void Quit();

  void Update();
  void Render();
  void Events();

  inline bool IsRunning() { return m_IsRunning; }

  inline SDL_Window *GetMainWindow() { return m_Window; }
  inline SDL_Renderer *GetRenderer() { return m_Renderer; }

  inline int GetWidth() { return m_Width; }
  inline int GetHeight() { return m_Height; }
  inline void SetWidth(int width) { m_Width = width; }
  inline void SetHeight(int height) { m_Height = height; }

  static Engine *GetInstance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
  }

private:
  Engine() {}
  bool m_IsRunning;
  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;
  static Engine *s_Instance;
  int m_Width, m_Height;
};

#endif // ENGINE_H
