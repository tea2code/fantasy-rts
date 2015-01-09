#ifndef FRTS_POINTLISTEVENTVALUE
#define FRTS_POINTLISTEVENTVALUE

#include <frts/vanillaevent>

#include <region/Point.h>


namespace frts
{
    class PointListEventValue;

    /**
     * @brief Pointer to PointListEventValue.
     */
    using PointListEventValuePtr = std::shared_ptr<PointListEventValue>;

    /**
     * @brief A point list event value.
     */
    class PointListEventValue : public EventValue
    {
    public:
        /**
         * @brief Get the value.
         * @return The value.
         */
        virtual PointVector getValue() const = 0;

        /**
         * @brief Set the value.
         * @param value The value.
         */
        virtual void setValue(PointVector value) = 0;
    };
}

#endif // FRTS_POINTLISTEVENTVALUE

