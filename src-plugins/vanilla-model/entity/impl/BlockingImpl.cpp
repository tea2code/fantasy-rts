#include "BlockingImpl.h"


frts::BlockingImpl::BlockingImpl(bool wall, bool water)
    : wall{wall}, water{water}
{
}

bool frts::BlockingImpl::blocks(BlockingPtr other)
{
    return false;
}

bool frts::BlockingImpl::wall() const
{
    return wall;
}

bool frts::BlockingImpl::water() const
{
    return water;
}
