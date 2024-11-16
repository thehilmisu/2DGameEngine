#include "Slider.h"
#include "../Inputs/Input.h"

namespace Gui {

    Slider::Slider(Attr attr):Widget(attr){

        m_CanSlide = false;
        m_Orientation = HORIZONTAL;
        m_FillColor = GRAY;
        m_BorderColor = DARK;
        SetBorder(1);

        m_Gauge = new Rect(Attr(m_Ctxt, m_OffsetX, m_OffsetY, 200, 5));
        m_Gauge->m_FillColor = SUCCESS;

        m_Handler = new Rect(Attr(m_Ctxt, m_OffsetX, m_OffsetY-8, 20, 20));
        m_Handler->SetBorder(1);
        m_Handler->m_BorderColor = DARK;
        m_Handler->m_FillColor = GRAY;
    }

    void Slider::Events(){

        if(Input::GetInstance()->GetMouseButtonDown(LEFT)){
            Vector2D* mouse = Input::GetInstance()->GetMousePosition();
            const SDL_Point point = {mouse->X, mouse->Y};

            if(SDL_PointInRect(&point, &m_Handler->m_Shape))
               m_CanSlide = true;
        }
        else{
            m_CanSlide = false;
        }

        if(m_CanSlide){
            OnSlide();
        }
    }

    void Slider::OnSlide(){
        Vector2D* mousePos = Input::GetInstance()->GetMousePosition();
        int targetX = mousePos->X;

        if((mousePos->X - m_LastHandlerPos) < 0){
            targetX = (mousePos->X < m_OffsetX)? m_OffsetX : mousePos->X;
        }

        if((mousePos->X - m_LastHandlerPos) > 0){
            const int temp = (m_OffsetX + m_Width - m_Handler->m_Width);
            targetX = (mousePos->X > temp)? temp : mousePos->X;
        }

        m_Handler->SetX(targetX);
        m_LastHandlerPos = mousePos->X;
        std::cout << "Handler: " << m_Handler->m_OffsetX << " Rect: " << m_OffsetX << std::endl;
    }

    void Slider::Draw(){
        DrawRect();
        m_Gauge->DrawRect();
        m_Handler->DrawRect();
    }

    void Slider::Update(){

        Events();
        //PlaceInsideParrent();
    }

    void Slider::Clean(){
        delete m_Gauge;
        delete m_Handler;
    }
}
