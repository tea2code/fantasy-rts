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
        BlockingImpl(const IdPtr& type);

        void addBlock(const IdPtr& block) override;
        bool blocks(const BlockedByPtr& blockedBy) override;
        IdPtr getComponentType() const override;
        void removeBlock(const IdPtr& block) override;

    private:
        BaseBlocking blocking;
        IdPtr type;
    };

    /**
     * @brief Create new BlockedBy.
     * @param type The component type.
     * @return The BlockedBy.
     */
    inline BlockingPtr makeBlocking(const IdPtr& type)
    {
        assert(type != nullptr);

        return std::make_shared<BlockingImpl>(type);
    }
}

#endif // FRTS_BLOCKINGIMPL_H
