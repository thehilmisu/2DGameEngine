#include "Frame.h"
#include "../Inputs/Input.h"

namespace Gui {

    Frame::Frame(Attr attr): Widget(attr){

        m_CanDrag = false;
        m_FillColor = DARK;
        m_BorderColor = GRAY;
        SetBorder(WD_BORDER_THICKNESS);

        Attr topBarAttr = Attr(m_Ctxt, m_OffsetX, m_OffsetY, m_Width, WD_TOPBAR_HEIGHT);
        m_TopBar = new Rect(topBarAttr);
        m_TopBar->m_FillColor = GRAY;
    }

    void Frame::Draw(){

        DrawRect();
        m_TopBar->DrawRect();

        for(auto child : m_Children)
            child->Draw();
    }

    void Frame::Update(){

        Events();
        PlaceInsideParrent();

        for(auto child : m_Children)
            child->Update();

        m_TopBar->SetXY(m_OffsetX, m_OffsetY);
    }

    void Frame::AddChild(Widget* child){
        child->SetParent(this);
        PlaceInsideParrent();
        m_Children.push_back(child);
    }

    void Frame::PlaceInsideParrent(){
        Widget::PlaceInsideParrent();
    }

    void Frame::Events(){

        if(Input::GetInstance()->GetMouseButtonDown(LEFT)){
            Vector2D* mouse = Input::GetInstance()->GetMousePosition();
            const SDL_Point point = {mouse->X, mouse->Y};

            if(SDL_PointInRect(&point, &m_TopBar->m_Shape))
               m_CanDrag = true;
        }
        else{
            m_CanDrag = false;
        }

        if(m_CanDrag)
            OnDrag();
    }

    void Frame::OnDrag(){
        Vector2D* mouse = Input::GetInstance()->GetMousePosition();
        const int targetX = (mouse->X - m_Width/2);
        const int targetY = (mouse->Y - WD_TOPBAR_HEIGHT/2);
        SetXY(targetX, targetY);
    }

    void Frame::Clean(){

        for(auto child : m_Children){
            child->Clean();
            delete child;
        }

        delete m_TopBar;
    }
}

