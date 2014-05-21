#ifndef FRTS_BLOCKEDBY_H
#define FRTS_BLOCKEDBY_H

#include "Component.h"

#include <frts/shared>

#include <memory>


namespace frts
{
    class BlockedBy;

    /**
     * @brief Pointer to Blocking.
     */
    using BlockedByPtr = std::shared_ptr<BlockedBy>;

    /**
     * @brief Component describing by what a entity is blocked.
     */
    class BlockedBy : public Component
    {
    public:
        using Type = IdPtr;

    public:
        virtual ~BlockedBy() {}

        /**
         * @brief Add block type.
         * @param block The block type.
         */
        virtual void addBlock(Type block) = 0;

        /**
         * @brief Remove block type.
         * @param block The block type.
         */
        virtual void removeBlock(Type block) = 0;
    };
}

#endif // FRTS_BLOCKEDBY_H
