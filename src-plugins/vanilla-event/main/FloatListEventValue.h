#ifndef FRTS_FLOATLISTEVENTVALUE
#define FRTS_FLOATLISTEVENTVALUE

#include "EventValue.h"

#include <vector>


namespace frts
{
    class FloatListEventValue;

    /**
     * @brief Pointer to FloatListEventValue.
     */
    using FloatListEventValuePtr = std::shared_ptr<FloatListEventValue>;

    /**
     * @brief A float list event value.
     */
    class FloatListEventValue : public EventValue
    {
    public:
        /**
         * @brief The type.
         */
        using type = std::vector<double>;

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

#endif // FRTS_FLOATLISTEVENTVALUE

