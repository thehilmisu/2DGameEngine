#include "SpriteAnimation.h"
#include "../Graphics/TextureManager.h"

SpriteAnimation::SpriteAnimation(bool repeat) : Animation(repeat) {}

void SpriteAnimation::Update(float deltaTime) 
{
    m_CurrentFrame = (SDL_GetTicks() / m_Speed) % m_FrameCount;
}

void SpriteAnimation::Draw(std::string id, int x, int y, int width, int height, float scaleX, float scaleY, SDL_RendererFlip flip) 
{
    TextureManager::GetInstance()->DrawFrame(id, x, y, width, height, m_SpriteRow, m_CurrentFrame, flip);
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int speed) 
{
    m_TextureID = textureID;
    m_SpriteRow = spriteRow;
    m_FrameCount = frameCount;
    m_Speed = speed;
}