#ifndef FRTS_BASEENTITYIMPL_H
#define FRTS_BASEENTITYIMPL_H

#include <entity/Blocking.h>

#include <frts/shared>

#include <memory>


namespace frts
{
    class BaseEntityImpl;

    /**
     * @brief Pointer to BaseEntityImpl;
     */
    using BaseEntityImplPtr = std::shared_ptr<BaseEntityImpl>;

    /**
     * @brief Base implementation of common entity methods. Can be used as a Pimpl.
     */
    class BaseEntityImpl
    {
    public:
        /**
         * @brief The default sort order.
         */
        const static int defaultSortOrder = 0;

    public:
        /**
         * @param blockedBy Definition by which types this entity is blocked.
         * @param blocking Definition which types this entity blocks.
         * @param state The initial state.
         * @param sortOrder The sort order.
         */
        BaseEntityImpl(BlockingPtr blockedBy, BlockingPtr blocking,
                       IdPtr state, int sortOrder = defaultSortOrder);

        BlockingPtr getBlockedBy() const;
        BlockingPtr getBlocking() const;
        int getSortOrder() const;
        IdPtr getStateId() const;

        /**
         * @brief Set the sort order. Will only be used the next time this entity
         *        is added to a block.
         * @param sortOrder The sort order.
         */
        void setSortOrder(int sortOrder);

        /**
         * @brief Set the current state id.
         * @param state The state id.
         */
        void setStateId(IdPtr state);

    private:
        BlockingPtr blockedBy;
        BlockingPtr blocking;
        IdPtr state;
        int sortOrder;
    };

    /**
     * @brief Create a new base entity.
     * @param blockedBy Definition by which types this entity is blocked.
     * @param blocking Definition which types this entity blocks.
     * @param state The initial state.
     * @param sortOrder The sort order.
     * @return The base entity.
     */
    inline BaseEntityImplPtr makeBaseEntity(BlockingPtr blockedBy, BlockingPtr blocking,
                                            IdPtr state, int sortOrder = BaseEntityImpl::defaultSortOrder)
    {
        return std::make_shared<BaseEntityImpl>(blockedBy, blocking, state, sortOrder);
    }
}

#endif // FRTS_BASEENTITYIMPL_H
