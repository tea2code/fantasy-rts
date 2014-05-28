#include "BlockedByImpl.h"


frts::BlockedByImpl::BlockedByImpl(IdPtr type)
    : type{type}
{
}

void frts::BlockedByImpl::addBlock(IdPtr block)
{
    blocking.addBlock(block);
}

const frts::BlockedBy::BlockSet frts::BlockedByImpl::getBlocks() const
{
    return blocking.getBlocks();
}

frts::IdPtr frts::BlockedByImpl::getComponentType()
{
    return type;
}

void frts::BlockedByImpl::removeBlock(IdPtr block)
{
    blocking.removeBlock(block);
}
