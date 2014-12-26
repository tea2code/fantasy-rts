#ifndef FRTS_STRINGEVENTVALUE
#define FRTS_STRINGEVENTVALUE

#include "EventValue.h"

#include <string>


namespace frts
{
    class StringEventValue;

    /**
     * @brief Pointer to StringEventValue.
     */
    using StringEventValuePtr = std::shared_ptr<StringEventValue>;

    /**
     * @brief A string event value.
     */
    class StringEventValue : public EventValue
    {
    public:
        /**
         * @brief Get the value.
         * @return The value.
         */
        virtual std::string getValue() const = 0;

        /**
         * @brief Set the value.
         * @param value The value.
         */
        virtual void setValue(std::string value) = 0;
    };
}

#endif // FRTS_STRINGEVENTVALUE

