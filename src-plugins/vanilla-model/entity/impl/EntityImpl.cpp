#include "EntityImpl.h"

#include <algorithm>
#include <stdexcept>


frts::EntityImpl::EntityImpl()
    : components {}
{
}

void frts::EntityImpl::addComponent(ComponentPtr component)
{
    assert(component != nullptr);

    components[component->getComponentType()] = component;
}

frts::ComponentPtr frts::EntityImpl::getComponent(IdPtr type) const
{
    assert(type != nullptr);

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
    for (auto& pair : components)
    {
        result.push_back(pair.second);
    }
    return result;
}

bool frts::EntityImpl::hasComponent(IdPtr type) const
{
    assert(type != nullptr);

    return getComponent(type) != nullptr;
}

void frts::EntityImpl::removeComponent(IdPtr type)
{
    assert(type != nullptr);

    components.erase(type);
}
