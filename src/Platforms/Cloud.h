#ifndef CLOUD_H
#define CLOUD_H

#include "SDL2/SDL.h"
#include "../Object/GameObject.h"
#include "../Graphics/TextureManager.h"
#include "../Factory/ObjectFactory.h"

class Cloud : public GameObject {

    public:
        Cloud(Transform* tf): GameObject(tf){
            int imgW, imgH;
            SDL_Texture* texture = TextureManager::GetInstance()->GetTexture(tf->TextureID);
            SDL_QueryTexture(texture, NULL, NULL, &imgW, &imgH);
            m_Tf->Width = imgW;
            m_Tf->Height = imgH;
        }

        virtual void Update(float dt) override{
            m_Tf->X -= dt;
            GameObject::Update(dt);
        }

};

static Registrar<StaticObject> cloud("CLOUD");

#endif // CLOUD_H
