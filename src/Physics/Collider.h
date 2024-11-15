#ifndef COLLIDER_H
#define COLLIDER_H

#include "SDL2/SDL.h"
#include "../Camera/Camera.h"
#include "../Physics/Vector2D.h"
#include "../Collision/CollisionHandler.h"

class Collider 
{
    public:
        inline SDL_Rect Get() { return m_Box; }    
        inline void SetOffset(int x, int y, int w, int h) { m_Offset = {x, y, w, h}; }

        void Set(int x, int y, int w, int h)
        {
            m_Box = { x - m_Offset.x, y - m_Offset.y, w - m_Offset.w, h - m_Offset.h};
        }

        bool CollideWithMap()
        {
            return CollisionHandler::GetInstance()->MapCollision(m_Box);
        }

        void Draw()
        {
            Vector2D cam = Camera::GetInstance()->GetPosition();
            SDL_Rect box = {static_cast<int>(m_Box.x - cam.X), static_cast<int>(m_Box.y - cam.Y), m_Box.w, m_Box.h};
          
            SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
        }
        
    private:
        SDL_Rect m_Box;
        SDL_Rect m_Offset; 
};

#endif // COLLIDER_H
