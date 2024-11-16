#ifndef PLAY_H
#define PLAY_H

#include "GameState.h"
#include "Menu.h"

#include "../Map/TileMap.h"
#include "../Object/GameObject.h"
#include "SDL2/SDL.h"
#include "../Core/Engine.h"
#include "../Graphics/TextureManager.h"
#include "../Map/MapParser.h"
#include "../Factory/ObjectFactory.h"
#include "../Characters/Warrior.h"
#include "../Characters/Enemy.h"
#include "../Camera/Camera.h"
#include "../Map/TileLayer.h"
#include "../Collision/CollisionHandler.h"
#include "../Timer/Timer.h"
#include "../Inputs/Input.h"
#include "../Map/ImgLayer.h"

class Play : public GameState{

    public:
        Play();
        void Events();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update();
        virtual void Render();
        //inline GameMap* GetMap(){return m_LevelMap;}

    private:
        static void OpenMenu();
        static void PauseGame();

    private:
        bool m_EditMode;
        TileMap* m_LevelMap;
        std::vector<ImgLayer*>  m_ParalaxBg;
        std::vector<GameObject*> m_GameObjects;
};

#endif // PLAY_H