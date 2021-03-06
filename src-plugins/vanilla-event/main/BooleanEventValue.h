#ifndef FRTS_BOOLEANEVENTVALUE
#define FRTS_BOOLEANEVENTVALUE

#include "EventValue.h"


namespace frts
{
    class BooleanEventValue;

    /**
     * @brief Pointer to BooleanEventValue.
     */
    using BooleanEventValuePtr = std::shared_ptr<BooleanEventValue>;

    /**
     * @brief A boolean event value.
     */
    class BooleanEventValue : public EventValue
    {
    public:
        /**
         * @brief The type.
         */
        using type = bool;

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

#endif // FRTS_BOOLEANEVENTVALUE

