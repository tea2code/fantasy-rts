#ifndef FRTS_BLOCKINGIMPL_H
#define FRTS_BLOCKINGIMPL_H

#include <entity/Blocking.h>


namespace frts
{
    class BlockingImpl : Blocking
    {
    public:
        BlockingImpl(bool wall, bool water);

        bool blocks(BlockingPtr other) override;
        bool wall() const override;
        bool water() const override;

    private:
        bool wall;
        bool water;
    };

    inline BlockingPtr makeBlocking(bool wall, bool water)
    {
        return std::make_shared<BlockingImpl>(wall, water);
    }
}

#endif // FRTS_BLOCKINGIMPL_H
