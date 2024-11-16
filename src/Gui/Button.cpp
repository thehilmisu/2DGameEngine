#include "Button.h"

namespace Gui{

    Button::Button(Attr attr, void (*clickAction)()) : Widget(attr){
        m_ClickAction = clickAction;
        SetBorder(BTN_BORDER_THICKNESS);
    }

    void Button::Draw(){
        DrawRect();
    }

    void Button::Update(){

        PlaceInsideParrent();

        Vector2D* mouse = Input::GetInstance()->GetMousePosition();
        SDL_Point point = {mouse->X, mouse->Y};

        if(SDL_PointInRect(&point, &m_Shape)){
            //clicked
            if(Input::GetInstance()->GetMouseButtonDown(LEFT) && m_IsReleased){
                m_IsReleased = false;
                m_ClickAction();
                m_FillColor = DARK;
            }
            //hover
            else if(!Input::GetInstance()->GetMouseButtonDown(LEFT)){
                m_IsReleased = true;
                m_FillColor = SECONDARY;
            }
        }
        // normal
        else{
            m_FillColor = GRAY;
        }
    }

    void Button::Clean(){

    }
}

