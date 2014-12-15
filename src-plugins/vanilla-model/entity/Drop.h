#ifndef FRTS_DROP_H
#define FRTS_DROP_H

#include "Component.h"

#include <memory>


namespace frts
{
    class Drop;

    /**
     * @brief Pointer to Drop.
     */
    using DropPtr = std::shared_ptr<Drop>;

    /**
     * @brief Component describing if an entity drops certain other entities if
     *        killed, destroyed, harvested...
     */
    class Drop : public Component
    {
    public:
        virtual ~Drop() {}

        /**
         * @brief Add entity to drop.
         * @param entityId The entity id.
         */
        virtual void addDrop(IdPtr entityId) = 0;

        /**
         * @brief Get all drops.
         * @return The entities.
         */
        virtual IdVector getDrops() const = 0;

        /**
         * @brief Check if entity has a certain drop.
         * @param entityId The entity id.
         * @return
         */
        virtual bool hasDrop(IdPtr entityId) const = 0;

        /**
         * @brief Remove entity to drop.
         * @param entityId The entity id.
         */
        virtual void removeDrop(IdPtr entityId) = 0;
    };
}

#endif // FRTS_DROP_H
