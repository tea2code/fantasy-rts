#ifndef FRTS_BLOCKEDBY_H
#define FRTS_BLOCKEDBY_H

#include "Component.h"
#include "Entity.h"

#include <frts/shared>

#include <memory>
#include <unordered_set>


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
        using BlockSet = std::unordered_set<IdPtr, IdHash, IdEqual>;

    public:
        virtual ~BlockedBy() {}

        /**
         * @brief Add block type.
         * @param block The block type.
         */
        virtual void addBlock(IdPtr block) = 0;

        /**
         * @brief Get all block types.
         * @return Set of block types.
         */
        virtual const BlockSet getBlocks() const = 0;

        /**
         * @brief Remove block type.
         * @param block The block type.
         */
        virtual void removeBlock(IdPtr block) = 0;
    };

    /**
     * @brief Get BlockedBy component if entity has it.
     * @param entity The entity.
     * @return The component or null.
     */
    inline BlockedByPtr getBlockedBy(EntityPtr entity)
    {
        auto component = entity->getComponent(BlockedBy::getComponentType());
        return std::static_pointer_cast<BlockedBy>(component);
    }
}

#endif // FRTS_BLOCKEDBY_H
