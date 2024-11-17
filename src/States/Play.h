#ifndef PLAY_H
#define PLAY_H

#include "GameState.h"

#include "../Map/TileMap.h"
#include "../Object/GameObject.h"
#include "SDL2/SDL.h"
#include "../Core/Engine.h"
#include "../Graphics/TextureManager.h"
#include "../Factory/ObjectFactory.h"
#include "../Characters/Warrior.h"
#include "../Characters/Enemy.h"
#include "../Camera/Camera.h"
#include "../Map/TileLayer.h"
#include "../Collision/CollisionHandler.h"
#include "../Timer/Timer.h"
#include "../Inputs/Input.h"
#include "../Parser/Parser.h"
#include "../Platforms/StaticObject.h"
#include "../Platforms/Cloud.h"


class Play : public GameState{

    public:
        Play();
        void Events();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update();
        virtual void Render();

    private:
        static void OpenMenu();
        static void PauseGame();

    private:
        bool m_DevMode;
        TileMap* m_LevelMap;
        ObjectList m_GameObjects;
        ObjectList m_SceneObjects;
};

#endif // PLAY_H