#ifndef SLIDER_H
#define SLIDER_H

#include "Widget.h"
#include "../Physics/Vector2D.h"

namespace Gui {

    enum Orientation {HORIZONTAL=0, VERTICAL=1};
    const float SLIDER_MAX_VALUE = 1.0f;
    const float SLIDER_MIN_VALUE = 0.0f;
    const float SLIDER_STEP = 0.1f;

    class Slider : public Widget {

        public:
            Slider(Attr attr);
            virtual void Draw();
            virtual void Clean();
            virtual void Update();

            void OnSlide();
            void Events();

        private:
            float m_Step;
            float m_Value;
            float m_MaxValue;
            float m_MinValue;

            bool m_CanSlide;
            Rect* m_Gauge;
            Rect* m_Handler;
            int m_LastHandlerPos;
            Orientation m_Orientation;
    };
}

#endif // SLIDER_H
