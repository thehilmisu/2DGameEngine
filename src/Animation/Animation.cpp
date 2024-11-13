#include "Animation.h"
#include "../Graphics/TextureManager.h"



void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight)
{
    if (m_UseMultipleImages)
    {
        TextureManager::GetInstance()->Draw(m_TextureIDs[m_SpriteFrame], x, y, spriteWidth, spriteHeight, m_Flip);
    }
    else
    {
        TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, m_Flip);
    }
}

void Animation::SetProps(std::vector<std::string> textureIDs, int animSpeed, SDL_RendererFlip flip)
{
    m_TextureIDs = textureIDs;
    m_FrameCount = textureIDs.size();
    m_AnimSpeed = animSpeed;
    m_Flip = flip;
    m_UseMultipleImages = true;
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed, SDL_RendererFlip flip)
{
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_AnimSpeed = animSpeed;
    m_Flip = flip;
    m_UseMultipleImages = false;
}

void Animation::Update()
{
    m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}
