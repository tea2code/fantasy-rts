#ifndef FRTS_BLOCKINGIMPL_H
#define FRTS_BLOCKINGIMPL_H

#include "BaseBlocking.h"

#include <entity/Blocking.h>


namespace frts
{
    class BlockingImpl : public Blocking
    {
    public:
        BlockingImpl();

        void addBlock(IdPtr block);
        bool blocks(BlockedByPtr blockedBy);
        void removeBlock(IdPtr block);

    private:
        BaseBlocking blocking;
    };

    /**
     * @brief Create new BlockedBy.
     * @return The BlockedBy.
     */
    inline BlockingPtr makeBlocking()
    {
        return std::shared_ptr<BlockingImpl>();
    }
}

#endif // FRTS_BLOCKINGIMPL_H
