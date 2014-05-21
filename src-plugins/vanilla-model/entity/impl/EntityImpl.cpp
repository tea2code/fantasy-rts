#include "EntityImpl.h"

#include <stdexcept>


frts::EntityImpl::EntityImpl()
{
}

void frts::EntityImpl::addComponent(ComponentPtr component)
{
    if (value == nullptr)
    {
        throw std::invalid_argument("Component must not be null.");
    }

    components[component->getComponentType()] = component;
}

frts::ComponentPtr frts::EntityImpl::getComponent(Component::Type type) const
{
    return components[type];
}

bool frts::EntityImpl::hasComponent(Component::Type type) const
{
    return components[type] != nullptr;
}

void frts::EntityImpl::removeComponent(Component::Type type)
{
    components.erase(type);
}
