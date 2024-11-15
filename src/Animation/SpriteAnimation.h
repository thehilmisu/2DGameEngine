#ifndef SPRITEANIMATION_H
#define SPRITEANIMATION_H

#include <string>
#include "SDL2/SDL.h"
#include "Animation.h"

class SpriteAnimation : public Animation {
public:
    SpriteAnimation(bool repeat = true);

    virtual void Update(float deltaTime);
    void Draw(std::string id, int x, int y, int width, int height, float scaleX=1.0f, float scaleY=1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void SetProps(std::string textureID, int spriteRow, int frameCount, int speed);

private:
    int m_Speed;
    int m_SpriteRow;
    int m_FrameCount;
    std::string m_TextureID;
};

#endif // SPRITEANIMATION_H