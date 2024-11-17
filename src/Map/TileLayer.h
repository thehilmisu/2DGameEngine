#ifndef TILELAYER_H
#define TILELAYER_H

#include <string>
#include <vector>
#include "../Physics/Vector2D.h"
#include "../Graphics/TextureManager.h"

struct Tileset{
    int FirstID, LastID;
    int Height, Width;
    int TileCount, TileSize;
    std::string Name, Source;
};

using TilesetsList = std::vector<Tileset> ;
using TileMatrix = std::vector<std::vector<int> >;

class TileLayer {

    public:
        TileLayer(int tilesize, int width, int rowcount, TileMatrix tilemap, TilesetsList tilesets):
        m_TileSize(tilesize), m_Width(width), m_Height(rowcount), m_Tilemap(tilemap), m_Tilesets(tilesets){}

        void Render(){
            for(int i = 0; i < m_Height; i++){
                for(int j = 0; j < m_Width; j++){

                    int tileID = m_Tilemap[i][j];
                    if(tileID == 0){
                        continue;
                    }else{
                        int index = 0;
                        if(m_Tilesets.size() > 1){
                            for(unsigned int k = 1; k < m_Tilesets.size(); k++){
                                if(tileID > m_Tilesets[k].FirstID && tileID < m_Tilesets[k].LastID){
                                    tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                                    index = k;
                                    break;
                                }
                            }
                        }

                        Tileset ts = m_Tilesets[index];
                        int tileRow = tileID/ts.Width;
                        int tileCol = tileID - tileRow*ts.Width-1;

                        // if this tile is on the las column
                        if(tileID % ts.Width == 0){
                            tileRow--;
                            tileCol = ts.Width - 1;
                        }

                        TextureManager::GetInstance()->DrawTile(ts.Name, j*ts.TileSize, i*ts.TileSize, ts.TileSize, tileRow, tileCol);
                    }
                }
            }
        }

        void Update(){}
        inline int GetTileSize(){return m_TileSize;}
        inline int GetWidth(){return m_Width*m_TileSize;}
        inline int GetHeight(){return m_Height*m_TileSize;}
        inline TileMatrix GetTileMap(){return m_Tilemap;}

    private:
        int m_TileSize, m_Width, m_Height;
        TileMatrix m_Tilemap;
        TilesetsList m_Tilesets;
        
};

#endif // TILELAYER_H
