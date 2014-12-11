#include "TeleportImpl.h"


frts::TeleportImpl::TeleportImpl(IdPtr type)
    : target{nullptr}, type{type}
{}

frts::IdPtr frts::TeleportImpl::getComponentType() const
{
    return type;
}

frts::EntityPtr frts::TeleportImpl::getTarget() const
{
    return target;
}

void frts::TeleportImpl::setTarget(EntityPtr target)
{
    this->target = target;
}
