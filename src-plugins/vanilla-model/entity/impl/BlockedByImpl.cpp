#include "BlockedByImpl.h"


frts::BlockedByImpl::BlockedByImpl(const IdPtr& type)
    : blocking{}, type{type}
{
}

void frts::BlockedByImpl::addBlock(const IdPtr& block)
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

void frts::BlockedByImpl::removeBlock(const IdPtr& block)
{
    assert(block != nullptr);

    blocking.removeBlock(block);
}
