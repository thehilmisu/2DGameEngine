#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "IObject.h"
#include "../Physics/Transform.h"
#include "SDL2/SDL.h"
#include "../Physics/Point.h"

struct Properties{

    public:
        Properties(float x, float y, int width, int height, const char* textureID = "",
                    SDL_RendererFlip flip = SDL_FLIP_NONE, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f){
            X = x;
            Y = y;
            Flip = flip;
            Width = width;
            Height = height;
            ScaleX = scaleX;
            ScaleY = scaleY;
            Rotation = rotation;
            TextureID = textureID;
        }

    public:
        float X, Y;
        float Rotation;
        int Width, Height;
        float ScaleX, ScaleY;
        const char* TextureID;
        SDL_RendererFlip Flip;
};

class GameObject : public IObject {

    public:
        GameObject(Properties* props){
            m_Width = props->Width;
            m_Height = props->Height;
            m_Flip = props->Flip;
            m_ScaleX = props->ScaleX;
            m_ScaleY = props->ScaleY;
            m_Rotation = props->Rotation;
            m_TextureID = props->TextureID;
            m_Transform = new Transform(props->X, props->Y);

            m_Transform = new Transform(props->X, props->Y);
            m_Origin = new Point(props->X + props->Width/2, props->Y + props->Height/2);
            delete props;
        }
        virtual ~GameObject()=default;
        virtual void Draw()=0;
        virtual void Clean()=0;
        virtual void Update(float dt)=0;

        inline Point* GetOrigin(){return m_Origin;}

    protected:

        float m_Rotation;
        int m_Width, m_Height;
        float m_ScaleX, m_ScaleY;

        Point* m_Origin;
        Transform* m_Transform;
        const char* m_TextureID;
        SDL_RendererFlip m_Flip;
};

#endif // GAMEOBJECT_H
