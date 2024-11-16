#include "Play.h"
#include "../Core/Log.h"
#include "Menu.h"
#include "Pause.h"


#include "../Gui/Frame.h"
#include "../Gui/Button.h"
#include "../Gui/Panel.h"
#include "../Gui/Slider.h"

//Gui::Frame* frame = nullptr;

Play::Play(){}

bool Play::Init(){
    m_EditMode = false;
    m_Ctxt = Engine::GetInstance()->GetRenderer();

    TextureManager::GetInstance()->Parse("assets/textures.tml");
    m_LevelMap = MapParser::GetInstance()->Load("assets/maps/map.tmx");
    TileLayer* collisionLayer = (TileLayer*)m_LevelMap->GetLayers().back();

    m_ParalaxBg.push_back(new ImgLayer("sky", 0, -50, 0.1, 3.0, 2.5));
    m_ParalaxBg.push_back(new ImgLayer("mountain", 0, 220, 0.2, 3.0, 2.5));

    m_ParalaxBg.push_back(new ImgLayer("cloud", 50, 60, 0.2));
    m_ParalaxBg.push_back(new ImgLayer("cloud", 1100, 60, 0.21));

    m_ParalaxBg.push_back(new ImgLayer("pine1", -10, 320, 0.3, 2.0, 2.0));
    m_ParalaxBg.push_back(new ImgLayer("pine1", 1366, 320, 0.3, 2.0, 2.0));

    m_ParalaxBg.push_back(new ImgLayer("pine2", -10, 400, 0.4, 2.0, 2.0));
    m_ParalaxBg.push_back(new ImgLayer("pine2", 1366, 400, 0.4, 2.0, 2.0));

    int tilesize = collisionLayer->GetTileSize();
    int width = collisionLayer->GetWidth()*tilesize;
    int height = collisionLayer->GetHeight()*tilesize;

    Camera::GetInstance()->SetSceneLimit(width, height);
    CollisionHandler::GetInstance()->SetCollisionMap(collisionLayer->GetTileMap(), tilesize);

    Warrior* warrior = new Warrior(new Properties(100, 200, 136, 96, "player_idle"));
    Enemy* enemy = new Enemy(new Properties(300, 200, 456, 348, "boss_appear"));
    
    Camera::GetInstance()->SetTarget(warrior->GetOrigin());
    
    m_GameObjects.push_back(warrior);
    m_GameObjects.push_back(enemy);


    // frame = new Gui::Frame(Gui::Attr(m_Ctxt, 100, 100, 500, 300));

    // Gui::Frame* f2 = new Gui::Frame(Gui::Attr(m_Ctxt, 100, 100, 250, 100));
    // f2->AddChild(new Gui::Button(Gui::Attr(m_Ctxt, 50, 50, 100, 35), OpenMenu));
    // frame->AddChild(new Gui::Button(Gui::Attr(m_Ctxt, 100, 50, 100, 35), PauseGame));

    // frame->AddChild(f2);

    CORE_INFO("Play state initialized");
    return true;
}

void Play::Render(){

    SDL_SetRenderDrawColor(m_Ctxt, 48, 96, 130, 255);
    SDL_RenderClear(m_Ctxt);

    for(auto imgLayer : m_ParalaxBg)
        imgLayer->Render();

    //draw trees
    for(int i=0; i<20; i++)
        TextureManager::GetInstance()->Draw("tree", 100+(i*100), 336, 80, 112, SDL_FLIP_NONE, 3.0, 4.0);
    

    m_LevelMap->Render();

    for(auto gameobj : m_GameObjects)
        gameobj->Draw();

    SDL_Rect camera = Camera::GetInstance()->GetViewBox();

    //frame->Draw();

    SDL_RenderCopy(m_Ctxt, nullptr, &camera, nullptr);
    SDL_RenderPresent(m_Ctxt);
}

void Play::Update(){

    Events();
    float dt = Timer::GetInstance()->GetDeltaTime();
    for(auto gameobj : m_GameObjects)
        gameobj->Update(dt);

    Camera::GetInstance()->Update();
    m_LevelMap->Update();

    //frame->Update();
}

void Play::Events(){

    if(m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_M))
        Engine::GetInstance()->ChangeState(new Menu());

    if(!m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
        m_EditMode = true;

    if(m_EditMode && Input::GetInstance()->GetKeyDown(SDL_SCANCODE_F5))
        m_EditMode = false;

    //SDL_Delay(100);
}

bool Play::Exit(){

    m_LevelMap->Clean();
    delete m_LevelMap;

    for(auto gameobj : m_GameObjects){
        gameobj->Clean();
        delete gameobj;
    }

    m_GameObjects.clear();
    TextureManager::GetInstance()->Clean();
    CORE_INFO("Play state exited");
    return true;
}

// callback action
void Play::OpenMenu(){
    Engine::GetInstance()->ChangeState(new Menu());
}

void Play::PauseGame(){
    Engine::GetInstance()->PushState(new Pause());
    CORE_INFO("Pause game");
}


