#include "BlockedByImpl.h"


frts::BlockedByImpl::BlockedByImpl(IdPtr type)
    : blocking{}, type{type}
{
}

void frts::BlockedByImpl::addBlock(IdPtr block)
{
    assert(block != nullptr);

    blocking.addBlock(block);
}

const frts::BlockedBy::BlockSet frts::BlockedByImpl::getBlocks() const
{
    return blocking.getBlocks();
}

frts::IdPtr frts::BlockedByImpl::getComponentType() const
{
    return type;
}

void frts::BlockedByImpl::removeBlock(IdPtr block)
{
    assert(block != nullptr);

    blocking.removeBlock(block);
}
