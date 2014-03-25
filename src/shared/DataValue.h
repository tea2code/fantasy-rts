#ifndef DATAVALUE_H
#define DATAVALUE_H

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
        virtual std::string getName() const = 0;
    };
}

#endif // DATAVALUE_H
