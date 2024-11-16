#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
#include "../Inputs/Input.h"

namespace Gui{

    const int BTN_BORDER_THICKNESS = 1;

    class Button : public Widget {

        public:
            Button(Attr attr, void (*clickAction)());
            virtual void Draw();
            virtual void Clean();
            virtual void Update();

        private:
            bool m_IsReleased;
            void (*m_ClickAction)();
    };
}
#endif // BUTTON_H
