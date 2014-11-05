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
        virtual std::string getName() const = 0;

        /**
         * @brief Get the module type name.
         * @return The name of the module type.
         */
        virtual std::string getTypeName() const = 0;

        /**
         * @brief Get the module type version.
         * @return Version number of the module type.
         */
        virtual int getTypeVersion() const = 0;

        /**
         * @brief Get the module version.
         * @return Version number of the module.
         */
        virtual int getVersion() const = 0;
    };
}

#endif // FRTS_DATAVALUE_H
