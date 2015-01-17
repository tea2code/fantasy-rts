#include "BlockingImpl.h"

#include <algorithm>
#include <iterator>


frts::BlockingImpl::BlockingImpl(const IdPtr& type)
    : blocking{}, type{type}
{
}

void frts::BlockingImpl::addBlock(const IdPtr& block)
{
    assert(block != nullptr);

    blocking.addBlock(block);
}

bool frts::BlockingImpl::blocks(const BlockedByPtr& blockedBy)
{
    if (blockedBy == nullptr)
    {
        return false;
    }

    auto blockedByBlocks = blockedBy->getBlocks();
    auto blockingBlocks = blocking.getBlocks();

    return std::any_of(blockingBlocks.begin(), blockingBlocks.end(),
                       [&](const IdPtr& block) { return blockedByBlocks.find(block) != blockedByBlocks.end(); });
}

frts::IdPtr frts::BlockingImpl::getComponentType() const
{
    return type;
}

void frts::BlockingImpl::removeBlock(const IdPtr& block)
{
    assert(block != nullptr);

    blocking.removeBlock(block);
}
