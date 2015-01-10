#ifndef FRTS_FLOATEVENTVALUE
#define FRTS_FLOATEVENTVALUE

#include "EventValue.h"


namespace frts
{
    class FloatEventValue;

    /**
     * @brief Pointer to FloatEventValue.
     */
    using FloatEventValuePtr = std::shared_ptr<FloatEventValue>;

    /**
     * @brief A float event value.
     */
    class FloatEventValue : public EventValue
    {
    public:
        /**
         * @brief The type.
         */
        using type = double;

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

#endif // FRTS_FLOATEVENTVALUE

