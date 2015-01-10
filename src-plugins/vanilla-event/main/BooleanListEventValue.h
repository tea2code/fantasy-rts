#ifndef FRTS_BOOLEANLISTEVENTVALUE
#define FRTS_BOOLEANLISTEVENTVALUE

#include "EventValue.h"

#include <vector>


namespace frts
{
    class BooleanListEventValue;

    /**
     * @brief Pointer to BooleanListEventValue.
     */
    using BooleanListEventValuePtr = std::shared_ptr<BooleanListEventValue>;

    /**
     * @brief A boolean list event value.
     */
    class BooleanListEventValue : public EventValue
    {
    public:
        /**
         * @brief The type.
         */
        using type = std::vector<bool>;

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

#endif // FRTS_BOOLEANLISTEVENTVALUE

