#include "Play.h"
#include "../Core/Log.h"

Play::Play(){}

bool Play::Init(){
    m_EditMode = false;
    m_Ctxt = Engine::GetInstance()->GetRenderer();

    TextureManager::GetInstance()->Parse("assets/textures.tml");
    m_LevelMap = MapParser::GetInstance()->Load("assets/maps/map.tmx");
    TileLayer* collisionLayer = (TileLayer*)m_LevelMap->GetLayers().back();

    int tilesize = collisionLayer->GetTileSize();
    int width = collisionLayer->GetWidth()*tilesize;
    int height = collisionLayer->GetHeight()*tilesize;

    CORE_INFO("tilesize: {0}, width: {1}, height: {2}", tilesize, width, height);

    Camera::GetInstance()->SetSceneLimit(width, height);
    CollisionHandler::GetInstance()->SetCollisionMap(collisionLayer->GetTileMap(), tilesize);

    Warrior* warrior = new Warrior(new Properties(100, 200, 136, 96, "player_idle"));
    Camera::GetInstance()->SetTarget(warrior->GetOrigin());
    m_GameObjects.push_back(warrior);

    CORE_INFO("Play state initialized");
    return true;
}

void Play::Render(){

    SDL_SetRenderDrawColor(m_Ctxt, 48, 96, 130, 255);
    SDL_RenderClear(m_Ctxt);

    m_LevelMap->Render();

    for(auto gameobj : m_GameObjects)
        gameobj->Draw();

    SDL_Rect camera = Camera::GetInstance()->GetViewBox();

    SDL_RenderCopy(m_Ctxt, nullptr, &camera, nullptr);
    SDL_RenderPresent(m_Ctxt);
}

void Play::Update(){

    Events();

    if(!m_EditMode){
        float dt = Timer::GetInstance()->GetDeltaTime();

        for(auto gameobj : m_GameObjects)
            gameobj->Update(dt);

        Camera::GetInstance()->Update();
        m_LevelMap->Update();
    }
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

}


