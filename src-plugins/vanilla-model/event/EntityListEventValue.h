#ifndef FRTS_ENTITYLISTEVENTVALUE
#define FRTS_ENTITYLISTEVENTVALUE

#include <frts/vanillaevent>

#include <entity/Entity.h>

#include <vector>


namespace frts
{
    class EntityListEventValue;

    /**
     * @brief Pointer to EntityListEventValue.
     */
    using EntityListEventValuePtr = std::shared_ptr<EntityListEventValue>;

    /**
     * @brief An entity list event value.
     */
    class EntityListEventValue : public EventValue
    {
    public:
        /**
         * @brief The type.
         */
        using type = EntityVector;

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

#endif // FRTS_ENTITYLISTEVENTVALUE

