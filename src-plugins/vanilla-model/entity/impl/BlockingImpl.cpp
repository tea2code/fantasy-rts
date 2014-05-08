#include "BlockingImpl.h"


frts::BlockingImpl::BlockingImpl(bool wall, bool water)
    : blocksWall{wall}, blocksWater{water}
{
}

bool frts::BlockingImpl::blocks(BlockingPtr other)
{
    bool wallBlocked = blocksWall && other->wall();
    bool waterBlocked = blocksWater && other->water();
    return wallBlocked || waterBlocked;
}

bool frts::BlockingImpl::wall() const
{
    return blocksWall;
}

bool frts::BlockingImpl::water() const
{
    return blocksWater;
}
