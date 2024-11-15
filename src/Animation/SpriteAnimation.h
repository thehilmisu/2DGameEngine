#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <string>
#include "SDL2/SDL.h"
#include "Animation.h"

class SpriteAnimation : public Animation {
 public:
    SpriteAnimation(bool repeat = true);

    virtual void Update(float dt);
    void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);
    void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip=SDL_FLIP_NONE, float scaleX=1.0, float scaleY=1.0, float rotation=0.0f, float speedRatio=1.0f);

private:
    int m_Speed;
    int m_SpriteRow;
    int m_FrameCount;
    std::string m_TextureID;
};

#endif // SPRITEANIMATION_H