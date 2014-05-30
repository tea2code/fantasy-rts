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
        BlockedByImpl(IdPtr type);

        void addBlock(IdPtr block) override;
        const BlockSet getBlocks() const override;
        IdPtr getComponentType() const override;
        void removeBlock(IdPtr block) override;

    private:
        BaseBlocking blocking;
        IdPtr type;
    };

    /**
     * @brief Create new BlockedBy.
     * @param type The component type.
     * @return The BlockedBy.
     */
    inline BlockedByPtr makeBlockedBy(IdPtr type)
    {
        return std::make_shared<BlockedByImpl>(type);
    }
}

#endif // FRTS_BLOCKEDBYIMPL_H
