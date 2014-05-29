#include "IsResourceImpl.h"


frts::IsResourceImpl::IsResourceImpl(IdPtr type)
    : type{type}
{
}

frts::IdPtr frts::IsResourceImpl::getComponentType()
{
    return type;
}
