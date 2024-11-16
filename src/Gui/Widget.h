#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <iostream>
#include "Rect.h"

namespace Gui{

    class Widget : public Rect {

        public:

            Widget();

            Widget(Attr attr) : Rect(attr){
                m_Parent = nullptr;
                m_LastParentX = m_LastParentY = 0;
            }

            virtual void PlaceInsideParrent(){
                if(m_Parent != nullptr){
                    if(!(m_LastParentX != m_Parent->GetX() || m_LastParentY != m_Parent->GetY()))
                        return;
                    else{
                        int targetX = m_OffsetX + (m_Parent->GetX() - m_LastParentX);
                        int targetY = m_OffsetY + (m_Parent->GetY() - m_LastParentY);
                        SetXY(targetX, targetY);

                        m_LastParentX = m_Parent->GetX();
                        m_LastParentY = m_Parent->GetY();
                    }
                }
            }

            virtual void AddChild(Widget* child){
                child->SetParent(this);
                m_Children.push_back(child);
            }

            void SetParent(Widget* parent){
                m_Parent = parent;
            }

            virtual void Draw() = 0;
            virtual void Clean() = 0;
            virtual void Update() = 0;

            inline const int GetX(){return m_OffsetX;}
            inline const int GetY(){return m_OffsetY;}
            inline const int GetWidth(){return m_Width;}
            inline const int GetHeight(){return m_Height;}

        protected:
            Widget* m_Parent;
            int m_LastParentX;
            int m_LastParentY;
            std::vector<Widget*> m_Children;
    };
}

#endif // WIDGET_H
