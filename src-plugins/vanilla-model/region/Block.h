#ifndef FRTS_BLOCK_H
#define FRTS_BLOCK_H

#include <entity/BlockedBy.h>
#include <entity/Entity.h>
#include <entity/SortOrder.h>

#include <frts/shared>

#include <memory>
#include <vector>


namespace frts
{
    class Block;

    /**
     * @brief Pointer to Block.
     */
    using BlockPtr = std::shared_ptr<Block>;

    /**
     * @brief A world block at a certain position consisting of entities.
     */
    class Block
    {
    public:
        virtual ~Block() {}

        /**
         * @brief Get all entities in this block which have a certain component.
         * @param componentType The type of component.
         * @return Entities ordered by their sort order component (if existing).
         */
        virtual std::vector<EntityPtr> getByComponent(IdPtr componentType) const = 0;

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
