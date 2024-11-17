#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <string>
#include "SDL2/SDL.h"
#include "../Object/Transform.h"
#include "../Graphics/TextureManager.h"
#include "Animation.h"

class SpriteAnimation : public Animation {
 public:
    SpriteAnimation(bool repeat = true);

    virtual void Update(float dt);
    void SetProps(int spriteRow, int frameCount, int speed);
    void Draw(Transform* tf);

private:
    int m_Speed;
    int m_SpriteRow;
    int m_FrameCount;
};

#endif // SPRITEANIMATION_H