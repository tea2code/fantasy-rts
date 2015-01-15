#ifndef FRTS_CONFIGNODE_H
#define FRTS_CONFIGNODE_H

#include "ConfigNodePtr.h"
#include <main/IteratorWrapper.h>

#include <string>
#include <vector>


namespace frts
{
    class ConfigNodeItr;

    /**
     * @brief Interface of configuration nodes.
     */
    class ConfigNode
    {
    public:
        /**
         * Iterator of ConfigNodes. See ConfigNodeItr.
         */
        using Iterator = IteratorWrapper<ConfigNodeItr, ConfigNodePtr, ConfigNodePtr, ConfigNodePtr>;

    public:
        virtual ~ConfigNode() {}

        /**
         * @brief If node is a list of node this allows iteration over it.
         * @return A begin iterator.
         */
        virtual Iterator begin() = 0;

        /**
         * @brief End iterator. See begin().
         * @return An end iterator.
         */
        virtual Iterator end() = 0;

        /**
         * @brief Get value as boolean.
         * @throws ConversionError if type conversion fails.
         * @throws MissingValueError if value is not found.
         * @param key Key of the value.
         * @return The value.
         */
        virtual bool getBool(const std::string& key) = 0;

        /**
         * @brief Get value as boolean or default value.
         * @param key Key of the value.
         * @param Default value if key is not found or conversion fails.
         * @return The value.
         */
        virtual bool getBool(const std::string& key, bool devaultValue) = 0;

        /**
         * @brief Get multiple boolean values in a list.
         * @throws ConversionError if type conversion fails.
         * @throws MissingValueError if values are not found.
         * @param key Key of the value list.
         * @return The values.
         */
        virtual std::vector<bool> getBools(const std::string& key) = 0;

        /**
         * @brief Get value as floating point number.
         * @throws ConversionError if type conversion fails.
         * @throws MissingValueError if value is not found.
         * @param key Key of the value.
         * @return The value.
         */
        virtual double getFloat(const std::string& key) = 0;

        /**
         * @brief Get value as floating point number or default value.
         * @param key Key of the value.
         * @param Default value if key is not found or conversion fails.
         * @return The value.
         */
        virtual double getFloat(const std::string& key, double devaultValue) = 0;

        /**
         * @brief Get multiple floating point values in a list.
         * @throws ConversionError if type conversion fails.
         * @throws MissingValueError if values are not found.
         * @param key Key of the value list.
         * @return The values.
         */
        virtual std::vector<double> getFloats(const std::string& key) = 0;

        /**
         * @brief Get value as integer number.
         * @throws ConversionError if type conversion fails.
         * @throws MissingValueError if value is not found.
         * @param key Key of the value.
         * @return The value.
         */
        virtual long getInteger(const std::string& key) = 0;

        /**
         * @brief Get value as integer number or default value.
         * @param key Key of the value.
         * @param Default value if key is not found or conversion fails.
         * @return The value.
         */
        virtual long getInteger(const std::string& key, long devaultValue) = 0;

        /**
         * @brief Get multiple integer values in a list.
         * @throws ConversionError if type conversion fails.
         * @throws MissingValueError if values are not found.
         * @param key Key of the value list.
         * @return The values.
         */
        virtual std::vector<long> getIntegers(const std::string& key) = 0;

        /**
         * @brief Get sub node.
         * @throws MissingValueError if value is not found.
         * @param key Key of the value.
         * @return The value.
         */
        virtual ConfigNodePtr getNode(const std::string& key) = 0;

        /**
         * @brief Get value as string or default value.
         * @throws ConversionError if type conversion fails.
         * @throws MissingValueError if value is not found.
         * @param key Key of the value.
         * @return The value.
         */
        virtual std::string getString(const std::string& key) = 0;

        /**
         * @brief Get value as string.
         * @param key Key of the value.
         * @param Default value if key is not found or conversion fails.
         * @return The value.
         */
        virtual std::string getString(const std::string& key,
                                      const std::string& devaultValue) = 0;

        /**
         * @brief Get multiple string values in a list.
         * @throws ConversionError if type conversion fails.
         * @throws MissingValueError if values are not found.
         * @param key Key of the value list.
         * @return The values.
         */
        virtual std::vector<std::string> getStrings(const std::string& key) = 0;

        /**
         * @brief Check if a value exists.
         * @param key Key of the value.
         * @return True if value exists else false.
         */
        virtual bool has(const std::string& key) = 0;

        /**
         * @brief Checks if a value is a boolean.
         * @throws MissingValueError if value is not found.
         * @param key Key of the value.
         * @return True if type is correct else false.
         */
        virtual bool isBool(const std::string& key) = 0;

        /**
         * @brief Checks if a value is a floating point number.
         * @throws MissingValueError if value is not found.
         * @param key Key of the value.
         * @return True if type is correct else false.
         */
        virtual bool isFloat(const std::string& key) = 0;

        /**
         * @brief Checks if a value is an integer number.
         * @throws MissingValueError if value is not found.
         * @param key Key of the value.
         * @return True if type is correct else false.
         */
        virtual bool isInteger(const std::string& key) = 0;

        /**
         * @brief Checks if a value is a string.
         * @throws MissingValueError if value is not found.
         * @param key Key of the value.
         * @return True if type is correct else false.
         */
        virtual bool isString(const std::string& key) = 0;
    };

    /**
     * @brief Get integer with direct cast.
     * @throws ConversionError if type conversion fails.
     * @throws MissingValueError if value is not found.
     * @param node The configuration node.
     * @param key Key of the value.
     * @return The integer.
     */
    template<typename IntegerType>
    inline IntegerType getCastInteger(ConfigNodePtr node, const std::string& key)
    {
        return static_cast<IntegerType>(node->getInteger(key));
    }

    /**
     * @brief Get integer or default value with direct cast.
     * @param node The configuration node.
     * @param key Key of the value.
     * @param Default value if key is not found or conversion fails.
     * @return The integer.
     */
    template<typename IntegerType>
    inline IntegerType getCastInteger(ConfigNodePtr node, const std::string& key, IntegerType defaultValue)
    {
        return static_cast<IntegerType>(node->getInteger(key, static_cast<long>(defaultValue)));
    }
}

#endif // FRTS_CONFIGNODE_H
