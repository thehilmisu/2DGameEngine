#include "Parser.h"
#include "../Object/Transform.h"
#include "../Graphics/TextureManager.h"
#include "../Core/Log.h"

Parser* Parser::s_Instance = nullptr;

void Parser::ParseGameObjects(const std::string& source, ObjectList* target){

    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        CORE_ERROR("Failed to load: {0}", source);
        return;
    }

    TiXmlElement* root = xml.RootElement();

    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){

        if(e->Value() == std::string("object")){

            int x = 0, y = 0, width = 0, height = 0, flip = 0;
            double scX = 0, scY = 0;
            std::string objType;
            std::string texID;
            double sratio = 0.0;
            double rot = 0.0;
            int category = -1;

            objType = e->Attribute("type");
            texID = e->Attribute("texture");

            e->Attribute("x", &x);
            e->Attribute("y", &y);
            e->Attribute("rot", &rot);

            e->Attribute("w", &width);
            e->Attribute("h", &height);
            e->Attribute("flip", &flip);
            e->Attribute("category", &category);

            #if 0
                CORE_INFO("x: {0}, y: {1}, w: {2}, h: {3}, flip: {4}, category: {5}, texture: {6}, type:{7}", x, y, width, height, flip, category, texID, objType);
            #endif

            SDL_RendererFlip rflip;
            if(flip == 0){rflip = SDL_FLIP_NONE;}
            if(flip == 1){rflip = SDL_FLIP_HORIZONTAL;}
            if(flip == 2){rflip = SDL_FLIP_VERTICAL;}

            e->Attribute("sX", &scX);
            e->Attribute("sY", &scY);
            e->Attribute("sratio", &sratio);

            #if 0
                CORE_INFO("sx: {0}, sy: {1}", scX, scY);
            #endif


            auto tf = new Transform(x, y, width, height, texID, rflip, scX, scY, rot, sratio);
            auto object = ObjectFactory::Instance()->CreateObject(objType, tf);

            if(object != nullptr){
                target->push_back(std::move(object));
                #if 0
                    CORE_INFO("Object: added");
                #endif
            }else{
                CORE_ERROR("Object: nullptr");
            }

        }
    }

    CORE_INFO("{0} GameObjects Parsed!", source);
}

bool Parser::ParseTextures(std::string source){

    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cout << "Failed to load: " << source << std::endl;
        return false;
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("texture")){
            std::string id = e->Attribute("id");
            std::string source = e->Attribute("source");
            TextureManager::GetInstance()->Add(id, source);
        }
    }

    CORE_INFO("{0} Textures Parsed!", source);
    return true;
}

TileMap* Parser::ParseMap(std::string source){

    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error()){
        std::cerr << "Failed to load: " << source << std::endl;
        return nullptr;
    }

    TiXmlElement* root = xml.RootElement();

    int colcount, rowcount, tilesize = 0;
    root->Attribute("width", &colcount);
    root->Attribute("height", &rowcount);
    root->Attribute("tilewidth", &tilesize);

    // Parse Tile sets
    TilesetsList tilesets;
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("tileset")){
            tilesets.push_back(ParseTileset(e));
        }
    }

    // Parse Layers
    TileMap* gamemap = new TileMap();
    for(TiXmlElement* e=root->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("layer")){
            TileLayer* tilelayer = ParseTileLayer(e, tilesets, tilesize, rowcount, colcount);
            gamemap->m_MapLayers.push_back(tilelayer);
        }
    }

    CORE_INFO("{0} Map Parsed!", source);
    
    return gamemap;
}

Tileset Parser::ParseTileset(TiXmlElement* xmlTileset){
    Tileset tileset;
    tileset.Name = xmlTileset->Attribute("name");
    xmlTileset->Attribute("firstgid", &tileset.FirstID);
    xmlTileset->Attribute("tilecount", &tileset.TileCount);
    tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

    xmlTileset->Attribute("columns", &tileset.Width);
    tileset.Height = tileset.TileCount/tileset.Width;
    xmlTileset->Attribute("tilewidth", &tileset.TileSize);

    TiXmlElement* image = xmlTileset->FirstChildElement();
    tileset.Source = image->Attribute("source");
    return tileset;
}

TileLayer* Parser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetsList tilesets, int tilesize, int rowcount, int colcount){

    TiXmlElement* data;
    for(TiXmlElement* e=xmlLayer->FirstChildElement(); e!= nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("data")){
            data = e;
            break;
        }
    }

    // Parse Layer tile map
    std::string matrix(data->GetText());
    std::istringstream iss(matrix);
    std::string id;

    TileMatrix tilemap(rowcount, std::vector<int> (colcount, 0));
    for(int row = 0; row < rowcount; row++){
        for (int col = 0; col < colcount; col++){
            getline(iss, id, ',');
            std::stringstream convertor(id);
            convertor >> tilemap[row][col];

            if(!iss.good())
                break;
        }
    }

    return (new TileLayer(tilesize, colcount, rowcount, tilemap, tilesets));
}


