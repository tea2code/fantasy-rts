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
        virtual void addBlock(IdPtr block) = 0;

        /**
         * @brief Check if it blocks.
         * @param blockedBy The blocked describtion.
         * @return True if it blocks else false.
         */
        virtual bool blocks(BlockedByPtr blockedBy) = 0;

        /**
         * @brief Remove block type.
         * @param block The block type.
         */
        virtual void removeBlock(IdPtr block) = 0;
    };

    /**
     * @brief Get Blocking component if entity has it.
     * @param entity The entity.
     * @return The component or null.
     */
    inline BlockingPtr getBlocking(EntityPtr entity)
    {
        auto component = entity->getComponent(Blocking::getComponentType());
        return std::static_pointer_cast<Blocking>(component);
    }
}

#endif // FRTS_BLOCKING_H
