#ifndef IMAGELAYER_H
#define IMAGELAYER_H

#include <string>
#include "Layer.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class ImgLayer : public Layer {

    public:
        ImgLayer(std::string m_TextureID, int x, int y, float scrollRatio=1.0f, float scalex=1.0f, float scaley=1.0f);
        void SetScrollRatio(float scrollRatio){m_ScrollRatio = scrollRatio;}
        void SetOffset(int x, int y){m_OffsetX = x; m_OffsetY = y;}
        void SetRepeated(bool repeated){m_Repeated = repeated;}
        void QueryImage(std::string textureID);

        virtual void Render();
        virtual void Update();

    private:
        bool m_Repeated;
        float m_ScrollRatio;
        std::string m_TextureID;
        float m_ScaleX, m_ScaleY;
        int m_OffsetX, m_OffsetY;
        int m_ImgWidth, m_ImgHeight;
        SDL_RendererFlip m_Flip;
};

#endif // IMAGELAYER_H