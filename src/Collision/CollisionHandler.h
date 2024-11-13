#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "SDL2/SDL.h"
#include <vector>
#include "../Map/TileLayer.h"
#include "../Map/GameMap.h"

class CollisionHandler 
{
public:
    static CollisionHandler* GetInstance(){
        return s_Instance = ( s_Instance != nullptr) ? s_Instance : new CollisionHandler();
    }

    bool CheckCollision(SDL_Rect a, SDL_Rect b);
    bool MapCollision(const SDL_Rect& a);

private:
    CollisionHandler();
    TileMap m_CollisionTilemap;
    TileLayer* m_CollisionLayer;
    static CollisionHandler* s_Instance;

};

#endif // COLLISIONHANDLER_H