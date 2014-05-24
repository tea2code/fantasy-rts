#ifndef FRTS_BLOCKEDBYIMPL_H
#define FRTS_BLOCKEDBYIMPL_H

#include "BaseBlocking.h"

#include <entity/BlockedBy.h>


namespace frts
{
    class BlockedByImpl : public BlockedBy
    {
    public:
        BlockedByImpl();

        void addBlock(IdPtr block) override;
        const BlockSet getBlocks() const override;
        void removeBlock(IdPtr block) override;

    private:
        BaseBlocking blocking;
    };

    /**
     * @brief Create new BlockedBy.
     * @return The BlockedBy.
     */
    inline BlockedByPtr makeBlockedBy()
    {
        return std::shared_ptr<BlockedByImpl>();
    }
}

#endif // FRTS_BLOCKEDBYIMPL_H
