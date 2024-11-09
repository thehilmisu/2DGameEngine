#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "Layer.h"
#include <vector>

class GameMap
{
    public:
        void Render()
        {
            for(size_t i = 0; i < m_MapLayers.size(); i++)
            {
                m_MapLayers.at(i)->Render();
            }
        }
        void Update()
        {
            for(size_t i = 0; i < m_MapLayers.size(); i++)
            {
                m_MapLayers.at(i)->Update();
            }
        }

        std::vector<Layer*> GetMapLayers() { return m_MapLayers; }

    private:
        std::vector<Layer*> m_MapLayers;
};

#endif