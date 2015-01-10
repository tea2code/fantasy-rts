#ifndef FRTS_IDLISTEVENTVALUE
#define FRTS_IDLISTEVENTVALUE

#include "EventValue.h"
#include <frts/shared>

#include <vector>


namespace frts
{
    class IdListEventValue;

    /**
     * @brief Pointer to IdListEventValue.
     */
    using IdListEventValuePtr = std::shared_ptr<IdListEventValue>;

    /**
     * @brief An id list event value.
     */
    class IdListEventValue : public EventValue
    {
    public:
        /**
         * @brief The type.
         */
        using type = IdVector;

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

#endif // FRTS_IDLISTEVENTVALUE

