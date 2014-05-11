#ifndef FRTS_TILEIMPL_H
#define FRTS_TILEIMPL_H

#include <entity/Tile.h>
#include <entity/impl/BaseEntityImpl.h>

#include <frts/shared>

#include <memory>


namespace frts
{
    class TileImpl : public Tile
    {
    public:
        TileImpl(BlockingPtr blockedBy, BlockingPtr blocking,
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
     * @brief Create a new resource.
     * @param blockedBy Definition by which types this entity is blocked.
     * @param blocking Definition which types this entity blocks.
     * @param state The initial state.
     * @param sortOrder The sort order.
     * @return The base entity.
     */
    inline TilePtr makeTile(BlockingPtr blockedBy, BlockingPtr blocking,
                            IdPtr state, int sortOrder = Entity::defaultSortOrder)
    {
        return std::make_shared<TileImpl>(blockedBy, blocking, state, sortOrder);
    }
}

#endif // FRTS_TILEIMPL_H
