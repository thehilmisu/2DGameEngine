#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "../States/GameState.h"

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

        void PopState();
        void PushState(GameState* current);
        void ChangeState(GameState* target);

        inline bool IsRunning(){return m_IsRunning;}
        inline SDL_Window* GetMainWindow(){return m_Window;}
        inline SDL_Renderer* GetRenderer(){return m_Renderer;}
        static Engine* GetInstance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new Engine();}

    private:
        Engine(){}
        bool m_IsRunning;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        static Engine* s_Instance;
        std::vector<GameState*> m_States;

};

#endif // ENGINE_H
