#include "Animation.h"
#include "../Graphics/TextureManager.h"



void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip)
{
    if (m_UseMultipleImages)
    {
        TextureManager::GetInstance()->DrawMultiple(m_TextureIDs[m_SpriteFrame], x, y, spriteWidth, spriteHeight, flip);
    }
    else
    {
        TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, spriteWidth, spriteHeight, m_SpriteRow, m_SpriteFrame, flip);
    }
}

void Animation::SetProps(std::vector<std::string> textureIDs, int animSpeed)
{
    m_TextureIDs = textureIDs;
    m_FrameCount = textureIDs.size();
    m_AnimSpeed = animSpeed;
    m_UseMultipleImages = true;
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int animSpeed)
{
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_AnimSpeed = animSpeed;
    m_UseMultipleImages = false;
}

void Animation::Update()
{
    m_SpriteFrame = (SDL_GetTicks() / m_AnimSpeed) % m_FrameCount;
}
