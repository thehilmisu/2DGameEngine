#ifndef COLLIDER_H
#define COLLIDER_H

#include "SDL2/SDL.h"
#include "../Camera/Camera.h"
#include "../Physics/Vector2D.h"
#include "../Collision/CollisionHandler.h"

class Collider {

    public:
        inline SDL_Rect Get(){return m_Box;}
        inline void SetBuffer(int x, int y, int w, int h){m_Buffer = {x, y, w, h};}

        void Set(int x, int y, int w, int h){
            m_Box = {
                x - m_Buffer.x,
                y - m_Buffer.y,
                w - m_Buffer.w,
                h - m_Buffer.h
            };
        }

        bool CollideWithMap(){
            return CollisionHandler::GetInstance()->MapCollision(m_Box);
        }

        void Draw(float speedRatio=1.0){
            Vector2D cam = Camera::GetInstance()->GetPosition() * speedRatio;
            SDL_Rect box = {static_cast<int>(m_Box.x - cam.X), static_cast<int>(m_Box.y - cam.Y), m_Box.w, m_Box.h};
            SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
        }

    private:
        SDL_Rect m_Box;
        SDL_Rect m_Buffer;
};

#endif // COLLIDER_H
