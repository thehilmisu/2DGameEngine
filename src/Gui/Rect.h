#ifndef Rect_H
#define Rect_H

#include "SDL2/SDL.h"
#include "Theme.h"

namespace Gui{

    struct Attr {
        SDL_Renderer* Context = nullptr;
        int OffsetX;
        int OffsetY;
        int Width;
        int Height;

        Attr(SDL_Renderer* ctxt, int x=0, int y=0, int w=200, int h=100)
        :Context(ctxt), OffsetX(x), OffsetY(y), Width(w), Height(h){}
    };

    class Rect {

        public:
            Rect(Attr attr){
                m_Ctxt = attr.Context;
                m_Width = attr.Width;
                m_Height = attr.Height;
                m_OffsetX = attr.OffsetX;
                m_OffsetY = attr.OffsetY;
                m_BorderThickness = 0;

                //m_FillColor = GRAY;
                //m_BorderColor = SECONDARY;

                //m_Border.x = m_OffsetX - m_BorderThickness;
                //m_Border.y = m_OffsetY - m_BorderThickness;
                //m_Border.w = m_Width + 2*m_BorderThickness;
                //m_Border.h = m_Height + 2*m_BorderThickness;
                m_Shape = {m_OffsetX, m_OffsetY, m_Width, m_Height};
            }

            void DrawRect(){

                if(m_BorderThickness > 0){
                    SDL_SetRenderDrawColor(m_Ctxt, m_BorderColor.r, m_BorderColor.g, m_BorderColor.b, m_BorderColor.a);
                    SDL_RenderFillRect(m_Ctxt, &m_Border);
                }

                SDL_SetRenderDrawColor(m_Ctxt, m_FillColor.r, m_FillColor.g, m_FillColor.b, m_FillColor.a);
                SDL_RenderFillRect(m_Ctxt, &m_Shape);
            }

            void SetX(int x){
                m_Shape.x = m_OffsetX = x;
                m_Border.x = m_Shape.x - m_BorderThickness;
            }

            void SetY(int y){
                m_Shape.y = m_OffsetY = y;
                m_Border.y = m_Shape.y - m_BorderThickness;
            }

            void SetXY(int x, int y){
                m_Shape.x = m_OffsetX = x;
                m_Shape.y = m_OffsetY = y;
                m_Border.x = m_Shape.x - m_BorderThickness;
                m_Border.y = m_Shape.y - m_BorderThickness;
            }

            void SetBorder(int border){
                m_BorderThickness = border;
                m_Border.x = m_OffsetX - border;
                m_Border.y = m_OffsetY - border;
                m_Border.w = m_Width + 2*border;
                m_Border.h = m_Height + 2*border;
            }

        public:
            int m_Width, m_Height;
            int m_OffsetX, m_OffsetY;

            SDL_Rect m_Shape;
            SDL_Rect m_Border;
            SDL_Renderer* m_Ctxt;

            int m_BorderRadius;
            int m_BorderThickness;
            SDL_Color m_FillColor;
            SDL_Color m_BorderColor;
    };
}
#endif // Rect_H
