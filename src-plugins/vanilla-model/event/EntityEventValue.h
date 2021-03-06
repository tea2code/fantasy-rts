#ifndef FRTS_ENTITYEVENTVALUE
#define FRTS_ENTITYEVENTVALUE

#include <frts/vanillaevent>

#include <entity/Entity.h>


namespace frts
{
    class EntityEventValue;

    /**
     * @brief Pointer to EntityEventValue.
     */
    using EntityEventValuePtr = std::shared_ptr<EntityEventValue>;

    /**
     * @brief An entity event value.
     */
    class EntityEventValue : public EventValue
    {
    public:
        /**
         * @brief The type.
         */
        using type = EntityPtr;

    public:
        /**
         * @brief Get the value.
         * @return The value.
         */
        virtual type getValue() const = 0;

        /**
         * @brief Set the value.
         * @param value The value.
         */
        virtual void setValue(type value) = 0;
    };
}

#endif // FRTS_ENTITYEVENTVALUE

