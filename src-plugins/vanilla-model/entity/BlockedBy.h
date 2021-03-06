#ifndef FRTS_BLOCKEDBY_H
#define FRTS_BLOCKEDBY_H

#include "Component.h"

#include <frts/shared>

#include <memory>


namespace frts
{
    class BlockedBy;

    /**
     * @brief Pointer to BlockedBy.
     */
    using BlockedByPtr = std::shared_ptr<BlockedBy>;

    /**
     * @brief Component describing by what a entity is blocked.
     */
    class BlockedBy : public Component
    {
    public:
        using BlockSet = IdUnorderedSet;

    public:
        virtual ~BlockedBy() {}

        /**
         * @brief Add block type.
         * @param block The block type.
         */
        virtual void addBlock(const IdPtr& block) = 0;

        /**
         * @brief Get all block types.
         * @return Set of block types.
         */
        virtual const BlockSet getBlocks() const = 0;

        /**
         * @brief Remove block type.
         * @param block The block type.
         */
        virtual void removeBlock(const IdPtr& block) = 0;
    };
}

#endif // FRTS_BLOCKEDBY_H
