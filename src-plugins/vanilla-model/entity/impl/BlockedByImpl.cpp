#include "BlockedByImpl.h"


frts::BlockedByImpl::BlockedByImpl()
{
}

void frts::BlockedByImpl::addBlock(IdPtr block)
{
    blocking.addBlock(block);
}

const frts::BlockedByImpl::BlockSet frts::BlockedByImpl::getBlocks() const
{
    return blocking.getBlocks();
}

void frts::BlockedByImpl::removeBlock(IdPtr block)
{
    blocking.removeBlock(block);
}
