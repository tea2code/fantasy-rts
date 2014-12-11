#include "BlockingImpl.h"

#include <algorithm>
#include <iterator>


frts::BlockingImpl::BlockingImpl(IdPtr type)
    : blocking{}, type{type}
{
}

void frts::BlockingImpl::addBlock(IdPtr block)
{
    blocking.addBlock(block);
}

bool frts::BlockingImpl::blocks(BlockedByPtr blockedBy)
{
    auto blockedByBlocks = blockedBy->getBlocks();
    auto blockingBlocks = blocking.getBlocks();

    // Following original implementation seems to fail in some cases.
//    BlockedBy::BlockSet intersect;
//    std::set_intersection(blockedByBlocks.begin(), blockedByBlocks.end(),
//                          blockingBlocks.begin(), blockingBlocks.end(),
//                          std::inserter(intersect, intersect.begin()));
//    return !intersect.empty();

    // TODO Replace naive implementation with something more smart and faster.
    for (auto block : blockingBlocks)
    {
        if (blockedByBlocks.find(block) != blockedByBlocks.end())
        {
            return true;
        }
    }
    return false;
}

frts::IdPtr frts::BlockingImpl::getComponentType() const
{
    return type;
}

void frts::BlockingImpl::removeBlock(IdPtr block)
{
    blocking.removeBlock(block);
}
