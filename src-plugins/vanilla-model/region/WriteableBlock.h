#ifndef FRTS_WRITEABLEBLOCK_H
#define FRTS_WRITEABLEBLOCK_H

#include "Block.h"

#include <memory>


namespace frts
{
    class WriteableBlock;

    /**
     * @brief Pointer to WriteableBlock.
     */
    using WriteableBlockPtr = std::shared_ptr<WriteableBlock>;

    class WriteableBlock : public Block
    {
    public:
        /**
         * @brief Get all entities in this block.
         * @return List of all entities.
         */
        virtual EntityVector getEntities() const = 0;

        /**
         * @brief Insert entity into block.
         * @param entity The entity.
         */
        virtual void insert(const EntityPtr& entity) = 0;

        /**
         * @brief Remove entity from block.
         * @param entity The entity.
         */
        virtual void remove(const EntityPtr& entity) = 0;
    };
}

#endif // FRTS_WRITEABLEBLOCK_H
