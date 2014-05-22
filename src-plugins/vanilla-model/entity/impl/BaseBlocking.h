#ifndef FRTS_BASEBLOCKING_H
#define FRTS_BASEBLOCKING_H

#include <entity/BlockedBy.h>


namespace frts
{
    class BaseBlocking
    {
    public:
        BaseBlocking();

        /**
         * @brief Add block.
         * @param block The block.
         */
        void addBlock(IdPtr block);

        /**
         * @brief Get all block types.
         * @return Set of block types.
         */
        const BlockedBy::BlockSet getBlocks() const;

        /**
         * @brief Remove block.
         * @param block The block.
         */
        void removeBlock(IdPtr block);

    private:
        BlockedBy::BlockSet blocks;
    };
}

#endif // FRTS_BASEBLOCKING_H
