#include "TileLayer.h"
#include "../Graphics/TextureManager.h"
#include "../Core/Log.h"

TileLayer::TileLayer(int tilesize, int rowcount, int colcount, TileMap tilemap, TilesetList tilesets) : 
                    m_TileSize(tilesize), m_RowCount(rowcount), m_ColCount(colcount), 
                    m_TileMap(tilemap), m_Tilesets(tilesets)
{
    for(size_t i = 0; i < m_Tilesets.size(); i++)
    {
        CORE_INFO("Loading tileset: Name = {}, Source = {}", m_Tilesets[i].Name, m_Tilesets[i].Source);
        if (m_Tilesets[i].Name.empty() || m_Tilesets[i].Source.empty())
        {
            CORE_ERROR("Tileset Name or Source is empty");
            continue;
        }
        TextureManager::GetInstance()->Load(m_Tilesets[i].Name, "/home/thehilmisu/Desktop/Workdir/2DGameEngine/assets/maps/" + m_Tilesets[i].Source);
    }
}

void TileLayer::Render()
{
    for(int i = 0; i < m_RowCount; i++)
    {
        for(int j = 0; j < m_ColCount; j++)
        {
            int tileID = m_TileMap[i][j];
            if(tileID == 0)
            {
                continue;
            }                
            else
            {
                int index = 0;
                if(m_Tilesets.size() > 1)
                {
                    for(size_t k = 1; k < m_Tilesets.size(); k++)
                    {
                        if(tileID > m_Tilesets[k].FirstID && tileID < m_Tilesets[k].LastID)
                        {
                            tileID = tileID + m_Tilesets[k].TileCount - m_Tilesets[k].LastID;
                            index = k;
                            break;
                        }
                    }
                }

                Tileset ts = m_Tilesets[index];
                //CORE_INFO("Rendering tile: tileID = {}, ts.Name = {}, ts.Source = {}", tileID, ts.Name, ts.Source);

                if(ts.ColCount <= 0)
                {
                    CORE_ERROR("Tileset ColCount is less than or equal to 0");
                    ts.ColCount = 1;
                }
                int tileRow = tileID / ts.ColCount;
                int tileCol = tileID - tileRow * ts.ColCount - 1;

                if(tileID % ts.ColCount == 0)
                {
                    tileRow--;
                    tileCol = ts.ColCount - 1;
                }

                TextureManager::GetInstance()->DrawTile(ts.Name, ts.TileSize, j * ts.TileSize, 
                                                        i * ts.TileSize, tileRow, tileCol);
            }
        }
    }
}

void TileLayer::Update()
{
}