#ifndef FRTS_BLOCKING_H
#define FRTS_BLOCKING_H

#include "BlockedBy.h"
#include "Component.h"

#include <memory>


namespace frts
{
    class Blocking;

    /**
     * @brief Pointer to Blocking.
     */
    using BlockingPtr = std::shared_ptr<Blocking>;

    /**
     * @brief Component describing what a entity blocks.
     */
    class Blocking : public Component
    {
    public:
        virtual ~Blocking() {}

        /**
         * @brief Add block type.
         * @param block The block type.
         */
        virtual void addBlock(const IdPtr& block) = 0;

        /**
         * @brief Check if it blocks.
         * @param blockedBy The blocked describtion. Null is a valid value and interpreted
         *                  as "blocked by nothing".
         * @return True if it blocks else false.
         */
        virtual bool blocks(const BlockedByPtr& blockedBy) = 0;

        /**
         * @brief Remove block type.
         * @param block The block type.
         */
        virtual void removeBlock(const IdPtr& block) = 0;
    };
}

#endif // FRTS_BLOCKING_H
