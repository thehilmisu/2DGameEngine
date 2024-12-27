#ifndef PANEL_H
#define PANEL_H

#include "SDL2/SDL.h"
#include "../Core/Engine.h"

namespace Ui{

    const SDL_Color STROKE = {135, 135, 135, 255};
    const SDL_Color FILL = {50, 50, 50, 255};

    class Panel {

        public:
            Panel(int x, int y, int w, int h, bool bordered=true) {
                Width = w;
                Height = h;
                OffsetX = x;
                OffsetY = y;
                Bordered = bordered;
                Ctxt = Engine::GetInstance()->GetRenderer();
                Rect = {OffsetX, OffsetY, Width, Height};
            }

            void Draw(){

                if(Bordered){
                    SDL_SetRenderDrawColor(Ctxt, STROKE.r, STROKE.g, STROKE.b, STROKE.a);
                    const SDL_Rect border = {Rect.x-1, Rect.y-1, Rect.w+2, Rect.h+2};
                    SDL_RenderDrawRect(Ctxt, &border);
                }

                SDL_SetRenderDrawColor(Ctxt, FILL.r, FILL.g, FILL.b, FILL.a);
                SDL_RenderFillRect(Ctxt, &Rect);
            }

        public:
            bool Bordered;
            SDL_Rect Rect;
            SDL_Renderer* Ctxt;
            int Width, Height;
            int OffsetX, OffsetY;
    };
}
#endif // RECT_H
