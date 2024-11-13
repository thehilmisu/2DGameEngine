#ifndef COLLIDER_H
#define COLLIDER_H

#include "SDL2/SDL.h"


class Collider 
{
    public:
        inline SDL_Rect Get() { return m_Box; }    
        inline void SetOffset(int x, int y, int w, int h) { m_Offset = {x, y, w, h}; }

        void Set(int x, int y, int w, int h)
        {
            m_Box = { x - m_Offset.x, y - m_Offset.y, w - m_Offset.w, h - m_Offset.h};
        }
        
    private:
        SDL_Rect m_Box;
        SDL_Rect m_Offset; 
};

#endif // COLLIDER_H
