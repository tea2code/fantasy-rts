#ifndef FRTS_BLOCKIMPL_H
#define FRTS_BLOCKIMPL_H

#include <region/Block.h>

#include <memory>
#include <stdexcept>


namespace frts
{
    class BlockImpl;

    /**
     * @brief Pointer to BlockImpl.
     */
    using BlockImplPtr = std::shared_ptr<BlockImpl>;

    class BlockImpl : public Block
    {
    public:
        BlockImpl();

        EntitySet getByType(Entity::Type type) const override;
        bool has(EntityPtr entity) const override;
        bool isBlocking(BlockingPtr blockedBy) const override;

        /**
         * @brief Insert entity into block.
         * @param entity The entity.
         */
        void insert(EntityPtr entity);

        /**
         * @brief Remove entity from block.
         * @param entity The entity.
         */
        void remove(EntityPtr entity);

    private:
        std::shared_ptr<EntitySet> dynamicEntities;
        std::shared_ptr<EntitySet> resources;
        std::shared_ptr<EntitySet> staticEntities;
        std::shared_ptr<EntitySet> tiles;

    private:
        std::shared_ptr<EntitySet> getPtrByType(Entity::Type type) const;
        bool isBlocking(std::shared_ptr<EntitySet> entitySet, BlockingPtr blockedBy) const;
        std::runtime_error makeUnknownTypeError(Entity::Type type) const;
    };

    inline BlockImplPtr makeBlock()
    {
        return std::make_shared<BlockImpl>();
    }
}

#endif // FRTS_BLOCKIMPL_H
