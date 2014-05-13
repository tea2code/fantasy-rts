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
         * @brief Insert entity into block.
         * @param entity The entity.
         */
        virtual void insert(EntityPtr entity) = 0;

        /**
         * @brief Remove entity from block.
         * @param entity The entity.
         */
        virtual void remove(EntityPtr entity) = 0;
    };
}

#endif // FRTS_WRITEABLEBLOCK_H