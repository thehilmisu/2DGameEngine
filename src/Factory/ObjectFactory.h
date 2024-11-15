#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include "../Object/GameObject.h"

class ObjectFactory {
public:
    GameObject* CreateObject(const std::string& type, Properties* props);
    void RegisterType(const std::string& className, std::function<GameObject*(Properties* props)> type);
    static ObjectFactory* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new ObjectFactory(); }

private:
    ObjectFactory() = default;
    ~ObjectFactory() = default;

    static ObjectFactory* s_Instance;
    std::unordered_map<std::string, std::function<GameObject*(Properties* props)>> m_TypeRegistry;
};

template<class Type>
class Registrar {
public:
    Registrar(const std::string& className) {
        ObjectFactory::GetInstance()->RegisterType(className, [] (Properties* props) -> GameObject* {
            return new Type(props);
        });
    }
};

#endif // OBJECT_FACTORY_H