#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <map>
#include <string>
#include "TileMap.h"
#include "tinyxml.h"
#include "TileLayer.h"

class MapParser {

   public:
        TileMap* Load(std::string filename);
        inline static MapParser* GetInstance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new MapParser();}

    private:
        MapParser(){}
        Tileset ParseTileset(TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, std::vector<Tileset> tilesets, int tilesize, int rowcount, int colcount);

        static MapParser* s_Instance;
};

#endif // MAPPARSER_H
