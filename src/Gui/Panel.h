#ifndef PANEL_H
#define PANEL_H

#include "Widget.h"

namespace Gui {

    class Panel : public Widget {

        public:

            Panel(Attr attr);
            virtual void Clean();
            virtual void Draw();
            virtual void Update();
    };

}

#endif // PANEL_H
