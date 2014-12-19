#include "BaseBlocking.h"


frts::BaseBlocking::BaseBlocking()
    : blocks{}
{
}

void frts::BaseBlocking::addBlock(IdPtr block)
{
    assert(block != nullptr);

    blocks.insert(block);
}

const frts::BlockedBy::BlockSet frts::BaseBlocking::getBlocks() const
{
    return blocks;
}

void frts::BaseBlocking::removeBlock(IdPtr block)
{
    assert(block != nullptr);

    blocks.erase(block);
}
