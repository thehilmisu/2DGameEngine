#include "Panel.h"

namespace Gui {

    Panel::Panel(Attr attr): Widget(attr) {
        m_Shape = {m_OffsetX, m_OffsetY, m_Width, m_Height};
        m_BorderColor = SECONDARY;
        m_FillColor = DARK;
    }

    void Panel::Clean(){
        for(auto widget : m_Children){
            widget->Clean();
            delete widget;
        }
    }

    void Panel::Draw(){
        DrawRect();
        for(auto widget : m_Children)
            widget->Draw();
    }

    void Panel::Update(){
        PlaceInsideParrent();
        for(auto widget : m_Children)
            widget->Update();
    }
}
