#include "TextureManager.h"
#include "../Core/Engine.h"
#include "../Core/Log.h"
#include "../Camera/Camera.h"
#include "tinyxml.h"

TextureManager* TextureManager::s_Instance = nullptr;

SDL_Texture* TextureManager::Load(std::string filename){

    SDL_Surface* surface = IMG_Load(filename.c_str());
    if(surface == nullptr){
        std::cout << "IMG_Load Failed: " << filename << " " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if(texture == nullptr){
        std::cout << "Failed to create surface: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    SDL_FreeSurface(surface);
    return texture;
}

bool TextureManager::Add(std::string id, std::string filename){

    if(m_TextureMap.count(id) > 0){
        std::cout << "Texture id: " << id << " already exist in map" << std::endl;
        return false;
    }
    else{
        SDL_Texture* texture = Load(filename);
        if(texture == nullptr){
            std::cout << "Texture id: "<< id << " is empty" << std::endl;
            return false;
        }
        m_TextureMap[id] = texture;
    }
    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int w, int h, SDL_RendererFlip flip, float scaleX, float scaleY, float rotation, float speedRatio){
    SDL_Rect srcRect = {0, 0, w, h};
    Vector2D cam = Camera::GetInstance()->GetPosition() * speedRatio;
    SDL_Rect dstRect = {static_cast<int>(x - cam.X), static_cast<int>(y - cam.Y), static_cast<int>(w * scaleX), static_cast<int>(h * scaleY)};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, rotation, nullptr, flip);
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
        std::cout << "Failed to load: " << source << std::endl;
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

    std::cout << source << " Parsed!" << std::endl;
    return true;
}

void TextureManager::Erase(std::string id){
    m_TextureMap.erase(id);
}

void TextureManager::Clean(){
    for(TextureMap::iterator it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
        SDL_DestroyTexture(it->second);
    m_TextureMap.clear();
    std::cout << "Texture Map is cleaned!" << std::endl;
}