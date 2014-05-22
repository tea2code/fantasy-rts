#include "EntityImpl.h"

#include <stdexcept>


frts::EntityImpl::EntityImpl()
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

frts::ComponentPtr frts::EntityImpl::getComponent(Component::ComponentType type) const
{
    ComponentPtr result = nullptr;
    auto it = components.find(type);
    if (it != components.end())
    {
        result = it->second;
    }
    return result;
}

bool frts::EntityImpl::hasComponent(Component::ComponentType type) const
{
    return getComponent(type) != nullptr;
}

void frts::EntityImpl::removeComponent(Component::ComponentType type)
{
    components.erase(type);
}
