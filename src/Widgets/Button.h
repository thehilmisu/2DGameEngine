#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
#include "../Inputs/Input.h"

namespace Ui{

    class Button : public Widget{

        public:
            Button(Vector2D offset, void (*click)());
            virtual void Show();
            virtual void Refresh();
            virtual void Destroy();

        private:
            bool m_IsReleased;
            void (*m_Click)();
    };
}

#endif // BUTTON_H
