#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include <vector>
#include "../Object/Transform.h"
#include "../Object/GameObject.h"

using ObjectPtr = std::unique_ptr<GameObject>;
using ObjectList = std::vector<ObjectPtr>;
enum ObjectCategory {SCENE_OBJECTS=0, GAME_OBJECTS=1};

class ObjectFactory{

    public:
        ObjectPtr CreateObject(std::string type, Transform* tf);
        void RegisterType(std::string className, std::function<ObjectPtr(Transform* tf)> type);
        static ObjectFactory* Instance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new ObjectFactory();}

    private:
        ObjectFactory(){}
        static ObjectFactory* s_Instance;
        std::map<std::string, std::function<ObjectPtr(Transform* tf)>> m_TypeRegistry;
};

template<class Type>
class Registrar {

    public:
        Registrar(std::string className){
            ObjectFactory::Instance()->RegisterType(className,
            [](Transform* tf)->ObjectPtr{
                return std::unique_ptr<Type>(new Type(tf));
            });
        }
};

#endif // OBJECT_FACTORY_H