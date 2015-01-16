#include "TeleportImpl.h"


frts::TeleportImpl::TeleportImpl(const IdPtr& type)
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

void frts::TeleportImpl::setTarget(const EntityPtr& target)
{
    assert(target != nullptr);

    this->target = target;
}
