#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"
#include "../Physics/Vector2D.h"
#include <vector>

enum MouseButtons{LEFT, MIDDLE, RIGHT};

enum Axis {HORIZONTAL, VERTICAL};

class Input{

    public:
        void Listen();
        int GetAxisKey(Axis axis);
        bool GetKeyDown(SDL_Scancode key){return (m_KeyStates[key] == 1)? true: false;}

        Vector2D* GetMousePosition(){return m_MousePosition;}
        bool GetMouseButtonDown(MouseButtons button) {return m_MouseButtonStates[button];}
        static Input* GetInstance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new Input();}

    private:
        Input();

        // keyboard event
        void KeyUp();
        void KeyDown();

        // mouse button event
        void MouseButtonUp(SDL_Event event);
        void MouseButtonDown(SDL_Event event);

        // mouse motion event
        void MouseMotion(SDL_Event event);

    private:
        const Uint8* m_KeyStates;
        static Input* s_Instance;
        Vector2D* m_MousePosition;
        std::vector<bool> m_MouseButtonStates;
};


#endif