#include "BlockingImpl.h"


frts::BlockingImpl::BlockingImpl(bool wall, bool water)
    : blocksWall{wall}, blocksWater{water}
{
}

bool frts::BlockingImpl::blocks(BlockingPtr other)
{
    bool blocksWall = wall() && other->wall();
    bool blocksWater = water() && other->water();
    return blocksWall || blocksWater;
}

bool frts::BlockingImpl::wall() const
{
    return blocksWall;
}

bool frts::BlockingImpl::water() const
{
    return blocksWater;
}
