#ifndef FRTS_STRINGLISTEVENTVALUE
#define FRTS_STRINGLISTEVENTVALUE

#include "EventValue.h"

#include <string>
#include <vector>


namespace frts
{
    class StringListEventValue;

    /**
     * @brief Pointer to StringListEventValue.
     */
    using StringListEventValuePtr = std::shared_ptr<StringListEventValue>;

    /**
     * @brief A string list event value.
     */
    class StringListEventValue : public EventValue
    {
    public:
        /**
         * @brief The type.
         */
        using type = std::vector<std::string>;

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

#endif // FRTS_STRINGLISTEVENTVALUE

