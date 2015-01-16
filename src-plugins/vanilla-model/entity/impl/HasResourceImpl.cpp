#include "HasResourceImpl.h"


frts::HasResourceImpl::HasResourceImpl(const IdPtr& type)
    : resources{}, type{type}
{
}

void frts::HasResourceImpl::addResource(const IdPtr& resourceType)
{
    assert(resourceType != nullptr);

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

bool frts::HasResourceImpl::hasResource(const IdPtr& resourceType) const
{
    assert(resourceType != nullptr);

    auto it = resources.find(resourceType);
    return it != resources.end();
}

void frts::HasResourceImpl::removeResource(const IdPtr& resourceType)
{
    assert(resourceType != nullptr);

    resources.erase(resourceType);
}
