#include "ObjectFactory.h"

ObjectFactory* ObjectFactory::s_Instance = nullptr;

void ObjectFactory::RegisterType(const std::string& className, std::function<GameObject*(Properties* props)> type)
{
    m_TypeRegistry[className] = type;
}

GameObject* ObjectFactory::CreateObject(const std::string& type, Properties* props)
{
    GameObject* obj = nullptr;
    auto it = m_TypeRegistry.find(type);
    
    if(it != m_TypeRegistry.end())
         obj = it->second(props);
 
    return obj;
}