#include "EntityImpl.h"

#include <algorithm>
#include <stdexcept>


frts::EntityImpl::EntityImpl()
    : components {}
{
}

void frts::EntityImpl::addComponent(ComponentPtr component)
{
    if (component == nullptr)
    {
        throw std::invalid_argument("Component must not be null.");
    }

    components[component->getComponentType()] = component;
}

frts::ComponentPtr frts::EntityImpl::getComponent(IdPtr type) const
{
    ComponentPtr result = nullptr;
    auto it = components.find(type);
    if (it != components.end())
    {
        result = it->second;
    }
    return result;
}

std::vector<frts::ComponentPtr> frts::EntityImpl::getComponents() const
{
    std::vector<ComponentPtr> result;
    for (auto pair : components)
    {
        result.push_back(pair.second);
    }
    return result;
}

bool frts::EntityImpl::hasComponent(IdPtr type) const
{
    return getComponent(type) != nullptr;
}

void frts::EntityImpl::removeComponent(IdPtr type)
{
    components.erase(type);
}
