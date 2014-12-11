#include "IsResourceImpl.h"


frts::IsResourceImpl::IsResourceImpl(IdPtr componentType)
    : componentType{componentType}, resourceType{}
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

void frts::IsResourceImpl::setResourceType(IdPtr resourceType)
{
    this->resourceType = resourceType;
}
