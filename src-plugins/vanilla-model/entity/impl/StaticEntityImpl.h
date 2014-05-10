#ifndef FRTS_STATICENTITYIMPL_H
#define FRTS_STATICENTITYIMPL_H

#include <entity/StaticEntity.h>
#include <entity/impl/BaseEntityImpl.h>

#include <frts/shared>

#include <memory>


namespace frts
{
    class StaticEntityImpl;

    /**
     * @brief Pointer to StaticEntityImpl.
     */
    using StaticEntityImplPtr = std::shared_ptr<StaticEntityImpl>;

    class StaticEntityImpl : public StaticEntity
    {
    public:
        StaticEntityImpl(BlockingPtr blockedBy, BlockingPtr blocking,
                         IdPtr state, int sortOrder = Entity::defaultSortOrder);

        BlockingPtr getBlockedBy() const;
        BlockingPtr getBlocking() const;
        int getSortOrder() const;
        IdPtr getStateId() const;
        Type getType() const;
        void setSortOrder(int sortOrder);
        void setStateId(IdPtr state);

    private:
        BaseEntityImpl baseEntity;
    };

    /**
     * @brief Create a new static entity.
     * @param blockedBy Definition by which types this entity is blocked.
     * @param blocking Definition which types this entity blocks.
     * @param state The initial state.
     * @param sortOrder The sort order.
     * @return The base entity.
     */
    inline StaticEntityImplPtr makeStaticEntity(BlockingPtr blockedBy, BlockingPtr blocking,
                                                IdPtr state, int sortOrder = Entity::defaultSortOrder)
    {
        return std::make_shared<StaticEntityImpl>(blockedBy, blocking, state, sortOrder);
    }
}

#endif // FRTS_STATICENTITYIMPL_H
