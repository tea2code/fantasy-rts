#include "HasResourceImpl.h"


frts::HasResourceImpl::HasResourceImpl(IdPtr type)
    : type{type}
{
}

frts::IdPtr frts::HasResourceImpl::getComponentType()
{
    return type;
}
