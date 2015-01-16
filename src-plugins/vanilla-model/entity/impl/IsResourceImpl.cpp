#include "IsResourceImpl.h"


frts::IsResourceImpl::IsResourceImpl(const IdPtr& componentType)
    : componentType{componentType}
{
}

frts::IdPtr frts::IsResourceImpl::getComponentType() const
{
    return componentType;
}

frts::IdPtr frts::IsResourceImpl::getResourceType() const
{
    return resourceType;
}

void frts::IsResourceImpl::setResourceType(const IdPtr& resourceType)
{
    assert(resourceType != nullptr);

    this->resourceType = resourceType;
}
