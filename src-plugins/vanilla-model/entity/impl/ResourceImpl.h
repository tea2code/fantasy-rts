#ifndef FRTS_RESOURCEIMPL_H
#define FRTS_RESOURCEIMPL_H

#include <entity/Resource.h>
#include <entity/impl/BaseEntityImpl.h>

#include <frts/shared>

#include <memory>


namespace frts
{
    class ResourceImpl;

    /**
     * @brief Pointer to ResourceImpl.
     */
    using ResourceImplPtr = std::shared_ptr<ResourceImpl>;

    class ResourceImpl : public Resource
    {
    public:
        ResourceImpl(BlockingPtr blockedBy, BlockingPtr blocking,
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
    inline ResourceImplPtr makeResource(BlockingPtr blockedBy, BlockingPtr blocking,
                                        IdPtr state, int sortOrder = Entity::defaultSortOrder)
    {
        return std::make_shared<ResourceImpl>(blockedBy, blocking, state, sortOrder);
    }
}

#endif // FRTS_RESOURCEIMPL_H