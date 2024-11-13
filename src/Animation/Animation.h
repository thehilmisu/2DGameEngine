#ifndef ANIMATION_H
#define ANIMATION_H

#include "SDL2/SDL.h"
#include <string>
#include <vector>


class Animation
{
    public:
        Animation(){}

        void Update();
        void Draw(float x, float y, int spriteWidth, int spriteHeight);
        void SetProps(std::string textureID, int spriteRow, int frameCount, 
                      int animSpeed, SDL_RendererFlip flip=SDL_FLIP_NONE);
        void SetProps(std::vector<std::string> textureIDs, int animSpeed, SDL_RendererFlip flip);

    private:
        std::vector<std::string> m_TextureIDs;
        bool m_UseMultipleImages = false;
        int m_SpriteRow, m_SpriteFrame;
        int m_AnimSpeed, m_FrameCount;
        std::string m_TextureID;
        SDL_RendererFlip m_Flip;

};  

#endif