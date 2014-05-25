#ifndef FRTS_BLOCKINGIMPL_H
#define FRTS_BLOCKINGIMPL_H

#include "BaseBlocking.h"
#include <entity/Blocking.h>

#include <frts/shared>


namespace frts
{
    class BlockingImpl : public Blocking
    {
    public:
        BlockingImpl(SharedManagerPtr shared);

        void addBlock(IdPtr block) override;
        bool blocks(BlockedByPtr blockedBy) override;
        IdPtr getComponentType() override;
        void removeBlock(IdPtr block) override;

    private:
        BaseBlocking blocking;
        IdPtr type;
    };

    /**
     * @brief Create new BlockedBy.
     * @param shared The shared manager.
     * @return The BlockedBy.
     */
    inline BlockingPtr makeBlocking(SharedManagerPtr shared)
    {
        return std::make_shared<BlockingImpl>(shared);
    }
}

#endif // FRTS_BLOCKINGIMPL_H
