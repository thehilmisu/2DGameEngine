#ifndef EDITOR_H
#define EDITOR_H


class Editor {

public:
  Editor();
  bool Init();
  void Update();
  void Render();

private:
  void RenderSideBar();
  void RenderBottomBar();
  void RenderTopBar();
};

#endif // EDITOR_H
