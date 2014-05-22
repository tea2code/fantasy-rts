#ifndef FRTS_BLOCK_H
#define FRTS_BLOCK_H

#include <entity/BlockedBy.h>
#include <entity/Entity.h>

#include <memory>
#include <set>


namespace frts
{
    class Block;

    /**
     * @brief Pointer to Block.
     */
    using BlockPtr = std::shared_ptr<Block>;

    /**
     * @brief Orders entities by sort order.
     */
    struct SortOrdered
    {
        bool operator() (EntityPtr lhs, EntityPtr rhs) const
        {
            return lhs->getSortOrder() < rhs->getSortOrder();
        }
    };

    /**
     * @brief A world block at a certain position consisting of entities.
     */
    class Block
    {
    public:
        using EntitySet = std::multiset<EntityPtr, SortOrdered>;

    public:
        virtual ~Block() {}

        /**
         * @brief Get all entities in this block by type.
         * @param type The entity type.
         * @return Ordered set of entities of given type.
         */
        virtual EntitySet getByType(Entity::Type type) const = 0;

        /**
         * @brief Check if block contains entity.
         * @param entity The entity.
         * @return True if block contains this entity else false.
         */
        virtual bool has(EntityPtr entity) const = 0;

        /**
         * @brief Check if block is blocking.
         * @param blockedBy The blocked by definition.
         * @return True if block is blocking.
         */
        virtual bool isBlocking(BlockedByPtr blockedBy) const = 0;
    };
}

#endif // FRTS_BLOCK_H
