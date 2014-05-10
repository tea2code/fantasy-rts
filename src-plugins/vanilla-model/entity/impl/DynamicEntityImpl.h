#ifndef FRTS_DYNAMICENTITYIMPL_H
#define FRTS_DYNAMICENTITYIMPL_H

#include <entity/DynamicEntity.h>
#include <entity/impl/BaseEntityImpl.h>

#include <frts/shared>

#include <memory>


namespace frts
{
    class DynamicEntityImpl;

    /**
     * @brief Pointer to DynamicEntityImpl.
     */
    using DynamicEntityImplPtr = std::shared_ptr<DynamicEntityImpl>;

    class DynamicEntityImpl : public DynamicEntity
    {
    public:
        DynamicEntityImpl(BlockingPtr blockedBy, BlockingPtr blocking,
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
     * @brief Create a new dynamic entity.
     * @param blockedBy Definition by which types this entity is blocked.
     * @param blocking Definition which types this entity blocks.
     * @param state The initial state.
     * @param sortOrder The sort order.
     * @return The base entity.
     */
    inline DynamicEntityImplPtr makeDynamicEntity(BlockingPtr blockedBy, BlockingPtr blocking,
                                                  IdPtr state, int sortOrder = Entity::defaultSortOrder)
    {
        return std::make_shared<DynamicEntityImpl>(blockedBy, blocking, state, sortOrder);
    }
}

#endif // FRTS_DYNAMICENTITYIMPL_H
