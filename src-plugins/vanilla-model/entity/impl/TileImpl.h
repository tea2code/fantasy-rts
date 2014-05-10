#ifndef FRTS_TILEIMPL_H
#define FRTS_TILEIMPL_H

#include <entity/Tile.h>
#include <entity/impl/BaseEntityImpl.h>

#include <frts/shared>

#include <memory>


namespace frts
{
    class TileImpl;

    /**
     * @brief Pointer to TileImpl.
     */
    using TileImplPtr = std::shared_ptr<TileImpl>;

    class TileImpl : public Tile
    {
    public:
        TileImpl(BlockingPtr blockedBy, BlockingPtr blocking,
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
     * @brief Create a new resource.
     * @param blockedBy Definition by which types this entity is blocked.
     * @param blocking Definition which types this entity blocks.
     * @param state The initial state.
     * @param sortOrder The sort order.
     * @return The base entity.
     */
    inline TileImplPtr makeTile(BlockingPtr blockedBy, BlockingPtr blocking,
                                IdPtr state, int sortOrder = Entity::defaultSortOrder)
    {
        return std::make_shared<TileImpl>(blockedBy, blocking, state, sortOrder);
    }
}

#endif // FRTS_TILEIMPL_H
