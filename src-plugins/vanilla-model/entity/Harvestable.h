#ifndef FRTS_HARVESTABLE
#define FRTS_HARVESTABLE

#include "Component.h"

#include <memory>


namespace frts
{
    class Harvestable;

    /**
     * @brief Pointer to Harvestable.
     */
    using HarvestablePtr = std::shared_ptr<Harvestable>;

    /**
     * @brief Component describing how the entity can be harvested.
     */
    class Harvestable : public Component
    {
    public:
        virtual ~Harvestable() {}

        /**
         * @brief Add harvest type.
         * @param type The harvest type.
         */
        virtual void addType(IdPtr type) = 0;

        /**
         * @brief Get the harvest speed.
         * @return The speed.
         */
        virtual double getSpeed() const = 0;

        /**
         * @brief Get all harvest types.
         * @return The harvest types.
         */
        virtual IdUnorderedSet getTypes() const = 0;

        /**
         * @brief Check if entity has a certain harvest type.
         * @param type The harvest type.
         * @return True if it has the harvest type else false.
         */
        virtual bool hasType(IdPtr type) const = 0;

        /**
         * @brief Remove harvest type.
         * @param type The Type.
         */
        virtual void removeType(IdPtr type) = 0;

        /**
         * @brief Set the harvest speed.
         * @param speed The speed.
         */
        virtual void setSpeed(double speed) = 0;
    };
}

#endif // FRTS_HARVESTABLE

