#include "BlockingImpl.h"

#include <algorithm>
#include <iterator>


frts::BlockingImpl::BlockingImpl()
{
}

void frts::BlockingImpl::addBlock(IdPtr block)
{
    blocking.addBlock(block);
}

bool frts::BlockingImpl::blocks(BlockedByPtr blockedBy)
{
    BlockedBy::BlockSet blockedByBlocks = blockedBy->getBlocks();
    BlockedBy::BlockSet blockingBlocks = blocking.getBlocks();

    BlockedBy::BlockSet intersect;
    std::set_intersection(blockedByBlocks.begin(), blockedByBlocks.end(),
                          blockingBlocks.begin(), blockingBlocks.end(),
                          std::inserter(intersect, intersect.begin()));

    return !intersect.empty();
}

void frts::BlockingImpl::removeBlock(IdPtr block)
{
    blocking.removeBlock(block);
}
