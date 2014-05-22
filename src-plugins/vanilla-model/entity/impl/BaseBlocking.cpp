#include "BaseBlocking.h"


frts::BaseBlocking::BaseBlocking()
{
}

void frts::BaseBlocking::addBlock(IdPtr block)
{
    blocks.insert(block);
}

const frts::BlockedBy::BlockSet frts::BaseBlocking::getBlocks() const
{
    return blocks;
}

void frts::BaseBlocking::removeBlock(IdPtr block)
{
    blocks.erase(block);
}
