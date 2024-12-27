#include "ObjectFactory.h"

ObjectFactory* ObjectFactory::s_Instance = nullptr;

void ObjectFactory::RegisterType(const std::string& className, std::function<ObjectPtr(Transform*)> creator) {
    m_FactoryMap[className] = creator;
}

ObjectPtr ObjectFactory::CreateObject(const std::string& className, Transform* tf) {
    auto it = m_FactoryMap.find(className);
    if (it != m_FactoryMap.end()) {
        return it->second(tf);
    }
    return nullptr;
}