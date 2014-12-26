#ifndef FRTS_INTEGEREVENTVALUE
#define FRTS_INTEGEREVENTVALUE

#include "EventValue.h"


namespace frts
{
    class IntegerEventValue;

    /**
     * @brief Pointer to IntegerEventValue.
     */
    using IntegerEventValuePtr = std::shared_ptr<IntegerEventValue>;

    /**
     * @brief An integer event value.
     */
    class IntegerEventValue : public EventValue
    {
    public:
        /**
         * @brief Get the value.
         * @return The value.
         */
        virtual long getValue() const = 0;

        /**
         * @brief Set the value.
         * @param value The value.
         */
        virtual void setValue(long value) = 0;
    };
}

#endif // FRTS_INTEGEREVENTVALUE

