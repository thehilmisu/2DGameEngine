#include "TextureManager.h"
#include "../Core/Engine.h"
#include "../Core/Log.h"
#include "../Camera/Camera.h"
#include "tinyxml.h"

TextureManager* TextureManager::s_Instance = nullptr;

SDL_Texture* TextureManager::Load(std::string filename){

    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr){
        CORE_ERROR("IMG_Load Failed: {0} {1}", filename, SDL_GetError());
        return nullptr;
    }

    #if 1
        CORE_INFO("Texture {0} loaded", filename);
    #endif

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if(texture == nullptr){
        CORE_ERROR("SDL_CreateTextureFromSurface Failed: {0}", SDL_GetError());
        return nullptr;
    }
    SDL_FreeSurface(surface);
    return texture;
}

bool TextureManager::Add(std::string id, std::string filename){

    if(m_TextureMap.count(id) > 0){
        CORE_INFO("Texture id: {0} already exist in map", id);
        return false;
    }
    else{
        SDL_Texture* texture = Load(filename);
        if(texture == nullptr){
            CORE_ERROR("Texture id: {0} is empty", id);
            return false;
        }
        CORE_INFO("Texture id: {0} loaded", id);
        m_TextureMap[id] = texture;
    }
    return true;
}

void TextureManager::DrawFrame(Transform* tf, int row, int frame){
    Vector2D cam = Camera::GetInstance()->GetPosition()*tf->ScrollRatio;
    SDL_Rect srcRect = {tf->Width*frame, tf->Height*row, tf->Width, tf->Height};
    SDL_Rect dstRect = {static_cast<int>(tf->X - cam.X), static_cast<int>(tf->Y - cam.Y), 
                        static_cast<int>(tf->Width*tf->ScaleX), static_cast<int>(tf->Height*tf->ScaleY)};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tf->TextureID], &srcRect, &dstRect, tf->Rotation, nullptr, tf->Flip);
}

void TextureManager::Draw(std::string id, int x, int y, int w, int h, SDL_RendererFlip flip, float scaleX, float scaleY, float rotation, float speedRatio){
    SDL_Rect srcRect = {0, 0, w, h};
    Vector2D cam = Camera::GetInstance()->GetPosition() * speedRatio;
    SDL_Rect dstRect = {static_cast<int>(x - cam.X), static_cast<int>(y - cam.Y), static_cast<int>(w * scaleX), static_cast<int>(h * scaleY)};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, rotation, nullptr, flip);
}

void TextureManager::Draw(Transform* tf){
    SDL_Rect srcRect = {0, 0, tf->Width, tf->Height};
    Vector2D cam = Camera::GetInstance()->GetPosition()*tf->ScrollRatio;
    SDL_Rect dstRect = {static_cast<int>(tf->X - cam.X), static_cast<int>(tf->Y - cam.Y), 
                        static_cast<int>(tf->Width*tf->ScaleX), static_cast<int>(tf->Height*tf->ScaleY)};
    //CORE_ERROR("tf->X: {0},{1},{2},{3},{4} ", tf->X, tf->Y, tf->TextureID,tf->Width, tf->Height);
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tf->TextureID], &srcRect, &dstRect, tf->Rotation, nullptr, tf->Flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int w, int h, int row, int frame, SDL_RendererFlip flip, float scaleX, float scaleY, float rotation, float speedRatio){
    SDL_Rect srcRect = {w * frame, h * row, w, h};
    Vector2D cam = Camera::GetInstance()->GetPosition() * speedRatio;
    SDL_Rect dstRect = {static_cast<int>(x - cam.X), static_cast<int>(y - cam.Y), static_cast<int>(w * scaleX), static_cast<int>(h * scaleY)};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, rotation, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int x, int y, int tilesize, int row, int col, float speedRatio){
    SDL_Rect srcRect = {tilesize * col, tilesize * row, tilesize, tilesize};
    Vector2D cam = Camera::GetInstance()->GetPosition() * speedRatio;
    SDL_Rect dstRect = {static_cast<int>(x - cam.X), static_cast<int>(y - cam.Y), tilesize, tilesize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, nullptr, SDL_FLIP_NONE);
}

bool TextureManager::Parse(std::string source){

    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        CORE_ERROR("Failed to load: {0}", source);
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("texture")){

            std::string id = e->Attribute("id");
            std::string source = e->Attribute("source");
            SDL_Texture* texture = Load(source);

            if(texture != nullptr)
                m_TextureMap[id] = texture;
        }
    }

    CORE_INFO("{0} Parsed!", source);
    return true;
}

void TextureManager::Erase(std::string id){
    m_TextureMap.erase(id);
}

void TextureManager::Clean(){
    for(TextureMap::iterator it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);
    m_TextureMap.clear();
    CORE_WARN("Texture Map is cleaned!");
}