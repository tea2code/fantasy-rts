#ifndef DATAVALUE_H
#define DATAVALUE_H

#include <memory>
#include <string>


namespace frts
{
    class DataValue;

    /**
     * @brief Pointer to DataValue.
     */
    using DataValuePtr = std::shared_ptr<DataValue>;

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