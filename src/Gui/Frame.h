#ifndef FRAME_H
#define FRAME_H

#include <string>
#include "Widget.h"
#include "Panel.h"

namespace Gui {

    const int WD_TOPBAR_HEIGHT = 35;
    const int WD_BORDER_THICKNESS = 2;

    class Frame : public Widget {

        public:
            Frame(Attr attr);
            virtual void Draw();
            virtual void Clean();
            virtual void Update();
            virtual void PlaceInsideParrent() override;
            virtual void AddChild(Widget* child);

            void OnDrag();
            void Events();

        private:
            bool m_CanDrag;
            Rect* m_TopBar;
    };
}

#endif // FRAME_H
