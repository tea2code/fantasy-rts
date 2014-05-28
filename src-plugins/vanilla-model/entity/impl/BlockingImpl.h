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
        BlockingImpl(IdPtr type);

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
     * @param type The component type.
     * @return The BlockedBy.
     */
    inline BlockingPtr makeBlocking(IdPtr type)
    {
        return std::make_shared<BlockingImpl>(type);
    }
}

#endif // FRTS_BLOCKINGIMPL_H
