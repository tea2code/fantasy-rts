#ifndef FRTS_DYNAMICENTITYIMPL_H
#define FRTS_DYNAMICENTITYIMPL_H

#include <entity/DynamicEntity.h>
#include <entity/impl/BaseEntityImpl.h>

#include <frts/shared>

#include <memory>


namespace frts
{
    class DynamicEntityImpl : public DynamicEntity
    {
    public:
        DynamicEntityImpl(BlockingPtr blockedBy, BlockingPtr blocking,
                          IdPtr state, int sortOrder = Entity::defaultSortOrder);

        BlockingPtr getBlockedBy() const override;
        BlockingPtr getBlocking() const override;
        int getSortOrder() const override;
        IdPtr getStateId() const override;
        Type getType() const override;
        void setSortOrder(int sortOrder) override;
        void setStateId(IdPtr state) override;

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
    inline DynamicEntityPtr makeDynamicEntity(BlockingPtr blockedBy, BlockingPtr blocking,
                                              IdPtr state, int sortOrder = Entity::defaultSortOrder)
    {
        return std::make_shared<DynamicEntityImpl>(blockedBy, blocking, state, sortOrder);
    }
}

#endif // FRTS_DYNAMICENTITYIMPL_H
