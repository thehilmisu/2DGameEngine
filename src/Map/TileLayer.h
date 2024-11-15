#ifndef TILELAYER_H
#define TILELAYER_H

#include <string>
#include <vector>
#include "Layer.h"
#include "../Physics/Vector2D.h"

struct Tileset{
    int FirstID, LastID;
    int Height, Width;
    int TileCount, TileSize;
    std::string Name, Source;
};

using TilesetsList = std::vector<Tileset> ;
using TileMap = std::vector<std::vector<int> >;

class TileLayer : public Layer {

    public:
        TileLayer(int tilesize, int width, int height, TileMap tilemap, TilesetsList tilesets);

        virtual void Render();
        virtual void Update();

        inline int GetWidth(){return m_Width;}
        inline int GetHeight(){return m_Height;}
        inline int GetTileSize(){return m_TileSize;}
        inline TileMap GetTileMap(){return m_Tilemap;}

    private:
        TileMap m_Tilemap;
        TilesetsList m_Tilesets;
        int m_TileSize, m_Width, m_Height;
};

#endif // TILELAYER_H
