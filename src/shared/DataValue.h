#ifndef FRTS_DATAVALUE_H
#define FRTS_DATAVALUE_H

#include <string>


namespace frts
{
    /**
     * @brief Interface representing a data value.
     */
    class DataValue
    {
    public:
        virtual ~DataValue() {}

        /**
         * @brief Get the name of the value.
         * @return Value name.
         */
        virtual std::string getName() const noexcept = 0;
    };
}

#endif // FRTS_DATAVALUE_H
