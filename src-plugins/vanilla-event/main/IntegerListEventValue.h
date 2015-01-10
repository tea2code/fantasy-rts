#ifndef FRTS_INTEGERLISTEVENTVALUE
#define FRTS_INTEGERLISTEVENTVALUE

#include "EventValue.h"

#include <vector>


namespace frts
{
    class IntegerListEventValue;

    /**
     * @brief Pointer to IntegerListEventValue.
     */
    using IntegerListEventValuePtr = std::shared_ptr<IntegerListEventValue>;

    /**
     * @brief An integer list event value.
     */
    class IntegerListEventValue : public EventValue
    {
    public:
        /**
         * @brief The type.
         */
        using type = std::vector<long>;

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

#endif // FRTS_INTEGERLISTEVENTVALUE

