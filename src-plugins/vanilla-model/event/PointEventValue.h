#ifndef FRTS_POINTEVENTVALUE
#define FRTS_POINTEVENTVALUE

#include <frts/vanillaevent>

#include <region/Point.h>


namespace frts
{
    class PointEventValue;

    /**
     * @brief Pointer to PointEventValue.
     */
    using PointEventValuePtr = std::shared_ptr<PointEventValue>;

    /**
     * @brief A point event value.
     */
    class PointEventValue : public EventValue
    {
    public:
        /**
         * @brief Get the value.
         * @return The value.
         */
        virtual PointPtr getValue() const = 0;

        /**
         * @brief Set the value.
         * @param value The value.
         */
        virtual void setValue(PointPtr value) = 0;
    };
}

#endif // FRTS_POINTEVENTVALUE

