#include "HasResourceImpl.h"


frts::HasResourceImpl::HasResourceImpl(IdPtr type)
    : type{type}
{
}

void frts::HasResourceImpl::addResource(IdPtr resourceType)
{
    resources.insert(resourceType);
}

frts::IdPtr frts::HasResourceImpl::getComponentType() const
{
    return type;
}

frts::HasResource::ResourceSet frts::HasResourceImpl::getResources() const
{
    return resources;
}

bool frts::HasResourceImpl::hasResource(IdPtr resourceType) const
{
    auto it = resources.find(resourceType);
    return it != resources.end();
}

void frts::HasResourceImpl::removeResource(IdPtr resourceType)
{
    resources.erase(resourceType);
}
