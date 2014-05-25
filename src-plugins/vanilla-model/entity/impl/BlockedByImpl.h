#ifndef FRTS_BLOCKEDBYIMPL_H
#define FRTS_BLOCKEDBYIMPL_H

#include "BaseBlocking.h"
#include <entity/BlockedBy.h>

#include <frts/shared>


namespace frts
{
    class BlockedByImpl : public BlockedBy
    {
    public:
        BlockedByImpl(SharedManagerPtr shared);

        void addBlock(IdPtr block) override;
        const BlockSet getBlocks() const override;
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
    inline BlockedByPtr makeBlockedBy(SharedManagerPtr shared)
    {
        return std::make_shared<BlockedByImpl>(shared);
    }
}

#endif // FRTS_BLOCKEDBYIMPL_H
