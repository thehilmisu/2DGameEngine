#ifndef MENU_H
#define MENU_H

#include "GameState.h"

class Menu : public GameState {

public:
  Menu();
  virtual bool Init();
  virtual bool Exit();
  virtual void Update();
  virtual void Render();

private:
  static void StartGame();
  static void Settings();
  static void Editor();
  static void Quit();
  void RenderSideBar();
  void RenderBottomBar();
  void RenderTopBar();
};

#endif // MENU_H
