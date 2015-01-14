#include "BlockingImpl.h"

#include <algorithm>
#include <iterator>


frts::BlockingImpl::BlockingImpl(IdPtr type)
    : blocking{}, type{type}
{
}

void frts::BlockingImpl::addBlock(IdPtr block)
{
    assert(block != nullptr);

    blocking.addBlock(block);
}

bool frts::BlockingImpl::blocks(BlockedByPtr blockedBy)
{
    assert(blockedBy != nullptr);

    auto blockedByBlocks = blockedBy->getBlocks();
    auto blockingBlocks = blocking.getBlocks();

    return std::any_of(blockingBlocks.begin(), blockingBlocks.end(),
                       [&](IdPtr block) { return blockedByBlocks.find(block) != blockedByBlocks.end(); });
}

frts::IdPtr frts::BlockingImpl::getComponentType() const
{
    return type;
}

void frts::BlockingImpl::removeBlock(IdPtr block)
{
    assert(block != nullptr);

    blocking.removeBlock(block);
}
