#ifndef FRTS_BASEENTITYIMPL_H
#define FRTS_BASEENTITYIMPL_H

#include <entity/Blocking.h>
#include <entity/Entity.h>

#include <frts/shared>

#include <memory>


namespace frts
{
    /**
     * @brief Base implementation of common entity methods. Can be used as a Pimpl.
     */
    class BaseEntityImpl
    {
    public:
        /**
         * @param blockedBy Definition by which types this entity is blocked.
         * @param blocking Definition which types this entity blocks.
         * @param state The initial state.
         * @param sortOrder The sort order.
         */
        BaseEntityImpl(BlockingPtr blockedBy, BlockingPtr blocking,
                       IdPtr state, int sortOrder = Entity::defaultSortOrder);

        BlockingPtr getBlockedBy() const;
        BlockingPtr getBlocking() const;
        int getSortOrder() const;
        IdPtr getStateId() const;
        void setSortOrder(int sortOrder);
        void setStateId(IdPtr state);

    private:
        BlockingPtr blockedBy;
        BlockingPtr blocking;
        IdPtr state;
        int sortOrder;
    };
}

#endif // FRTS_BASEENTITYIMPL_H
