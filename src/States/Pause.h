#ifndef PAUSE_H
#define PAUSE_H

#include "GameState.h"

class Pause: public GameState {

    public:
        Pause();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update();
        virtual void Render();

    private:
        static void Resume();
};

#endif // PAUSE_H
