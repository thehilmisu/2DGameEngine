#include "TextureManager.h"
#include "../Core/Engine.h"
#include "../Core/Log.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id, std::string  filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr)
    {
        CORE_ERROR("failed to load texture : {0}, {1}", filename.c_str(), SDL_GetError());
        return false;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if(texture == nullptr)
    {
        CORE_ERROR("failed to create texture from surface : {0}", SDL_GetError());
        return false;
    }

    m_TextureMap[id] = texture;
    CORE_INFO("texture loaded with id : {0}", id);

    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, 
                        SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    SDL_Rect dstRect = {x, y, width, height};

    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);

}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, 
                        int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width * frame, height * row, width, height};
    SDL_Rect dstRect = {x, y, width, height};

    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);

}

void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
    CORE_WARN("texture removed, id : {0}", id);
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for(it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);

    m_TextureMap.clear();

    CORE_INFO("texture map cleaned...");
}

