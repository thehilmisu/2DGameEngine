#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <map>

using TextureMap = std::map<std::string, SDL_Texture*>;


class TextureManager
{
    public:
        void Clean();
        void Erase(std::string id);
        bool Parse(std::string source);
        SDL_Texture* Load(std::string filename);
        bool Add(std::string id, std::string filename);
        TextureMap GetTextureMap(){return m_TextureMap;}

        void DrawTile(std::string tilesetID, int x, int y, int tilesize, int row, int col, float speedRatio=1.0f);

        void Draw(std::string id, int x, int y, int w, int h, SDL_RendererFlip flip=SDL_FLIP_NONE,
                  float scaleX=1.0f, float scaleY=1.0f, float rotation=0.0f, float speedRatio=1.0f);

        void DrawFrame(std::string id, int x, int y, int w, int h, int row, int frame, SDL_RendererFlip flip=SDL_FLIP_NONE,
                        float scaleX=1.0f, float scaleY=1.0f,  float rotation=0.0f, float speedRatio=1.0f);

        SDL_Texture* GetTexture(std::string id){return m_TextureMap[id];}

        static TextureManager* GetInstance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new TextureManager();}

    private:
        TextureManager(){}
        TextureMap m_TextureMap;
        static TextureManager* s_Instance;
};

#endif