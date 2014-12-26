#ifndef FRTS_IDEVENTVALUE
#define FRTS_IDEVENTVALUE

#include "EventValue.h"
#include <frts/shared>


namespace frts
{
    class IdEventValue;

    /**
     * @brief Pointer to IdEventValue.
     */
    using IdEventValuePtr = std::shared_ptr<IdEventValue>;

    /**
     * @brief An id event value.
     */
    class IdEventValue : public EventValue
    {
    public:
        /**
         * @brief Get the value.
         * @return The value.
         */
        virtual IdPtr getValue() const = 0;

        /**
         * @brief Set the value.
         * @param value The value.
         */
        virtual void setValue(IdPtr value) = 0;
    };
}

#endif // FRTS_IDEVENTVALUE

