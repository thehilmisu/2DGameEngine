#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <string>
#include <vector>
#include "../Map/TileMap.h"
#include "tinyxml.h"
#include "../Object/GameObject.h"
#include "../Map/TileLayer.h"
#include "../Factory/ObjectFactory.h"

class Parser {

   public:
        bool ParseTextures(std::string source);
        TileMap* ParseMap(std::string source);
        void ParseGameObjects(const std::string& source, ObjectList* target);
        //ObjectList& ParseGameObjects(std::string source);
        inline static Parser* Instance(){ return s_Instance = (s_Instance != nullptr)? s_Instance : new Parser();}

    private:
        Parser(){}
        Tileset ParseTileset(TiXmlElement* xmlTileset);
        TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, std::vector<Tileset> tilesets, int tilesize, int rowcount, int colcount);

    private:
        static Parser* s_Instance;
};

#endif // PARSER_H
