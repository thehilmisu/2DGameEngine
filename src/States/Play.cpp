#include "Play.h"
#include "../Core/Log.h"
#include "Menu.h"
#include "Pause.h"
#include "../States/StateManager.h"
#include <memory>

Play::Play() : m_DevMode(true) {}

bool Play::Init(){
    m_Ctxt = Engine::GetInstance()->GetRenderer();

    Parser::Instance()->ParseTextures("assets/textures.tml");
    m_LevelMap = Parser::Instance()->ParseMap("assets/maps/map.tmx");
    Parser::Instance()->ParseGameObjects("assets/level1.tml", &m_SceneObjects);

    CORE_ERROR("Scene objects: {0}", m_SceneObjects.size());

    TileLayer* colLayer = m_LevelMap->GetLayers().back();
    CollisionHandler::GetInstance()->SetCollisionLayer(colLayer);
    Camera::GetInstance()->SetLimit(colLayer->GetWidth(), colLayer->GetHeight());

    auto player = ObjectFactory::Instance()->CreateObject("WARRIOR", new Transform(200, 600, 136, 96, "player_idle"));
    Camera::GetInstance()->SetViewPort({0, 0, Engine::GetInstance()->GetWidth(), Engine::GetInstance()->GetHeight()});
    #if 0
        CORE_ERROR("Player origin: {0},{1}", std::to_string(player->GetOrigin()->X), std::to_string(player->GetOrigin()->Y));
    #endif
    Camera::GetInstance()->SetTarget(player->GetOrigin());
    
    m_GameObjects.push_back(std::move(player));

    CORE_ERROR("Game objects: {0}", m_GameObjects.size());

    CORE_INFO("Play initialized");

    return true;
}

void Play::Render(){

    SDL_SetRenderDrawColor(m_Ctxt, 45, 80, 82, 255);
    SDL_RenderClear(m_Ctxt);


    for(size_t i = 0; i < m_SceneObjects.size(); ++i)
        m_SceneObjects[i]->Draw();


    m_LevelMap->Render();

    // for(const auto& scene_obj : m_SceneObjects)
    //     scene_obj->Draw();

    for(const auto& object : m_GameObjects)
        object->Draw();

    SDL_RenderPresent(m_Ctxt);
}

void Play::Update(){

    Events();
    float dt = Timer::GetInstance()->GetDeltaTime();
    if(!m_DevMode)
    {

        for(auto& object : m_GameObjects)
            object->Update(dt);

        Camera::GetInstance()->TrackTarget();
        m_LevelMap->Update();

        for(auto& scene_obj : m_SceneObjects)
            scene_obj->Update(dt);
    }
}

void Play::Events(){

    if(m_DevMode)
    {

        if(Input::GetInstance()->GetMouseButtonDown(LEFT)){
            const Vector2D currMousePos = Input::GetInstance()->GetMousePosition();
            const SDL_Point point = {(int)currMousePos.X, (int)currMousePos.Y};
            const SDL_Rect viewport = Camera::GetInstance()->GetViewPort();

            if(SDL_PointInRect(&point, &viewport)){
                const Vector2D lastMousePos = Input::GetInstance()->GetMouseLastPosition();
                const Vector2D target = (currMousePos - lastMousePos)*-1;
                Camera::GetInstance()->Translate(target);
            }
        }

        //Camera::Instance()->TranslateX(10*Input::Instance()->GetAxisKey(HORIZONTAL));
        //Camera::Instance()->TranslateY(10*Input::Instance()->GetAxisKey(VERTICAL));
    }

    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_F5)){
        m_DevMode = false;
        CORE_WARN("DevMode: OFF");
    }
    if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_ESCAPE)){
        m_DevMode = true;
        CORE_WARN("DevMode: ON");
    }
}

bool Play::Exit(){

    m_LevelMap->Clean();
    delete m_LevelMap;

    for(auto& scene_obj : m_SceneObjects){
        scene_obj->Clean();
        scene_obj.release();
    }

    for(auto& object : m_GameObjects){
        object->Clean();
        object.release();
    }

    m_SceneObjects.clear();
    m_GameObjects.clear();
    TextureManager::GetInstance()->Clean();
    CORE_INFO("Play exited");
    return true;
}

void Play::OpenMenu(){
    StateManager::GetInstance()->ChangeState(new Menu());
    CORE_INFO("Menu");
}

void Play::PauseGame(){
    StateManager::GetInstance()->PushState(new Pause());
    CORE_INFO("Pause game");
}


