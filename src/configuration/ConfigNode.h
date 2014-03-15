#ifndef CONFIGNODE_H
#define CONFIGNODE_H

#include <map>
#include <string>
#include <vector>

namespace std
{
    template<class T>
    class shared_ptr;
}

namespace frts
{
    template<class IteratorImpl, class Value, class Reference, class Pointer>
    class IteratorWrapper;
    class ConfigNodeItr;
    class ConfigNode;

    /**
     * @brief Pointer to ConfigNodes.
     */
    using ConfigNodePtr = std::shared_ptr<ConfigNode>;

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
         * @param Key of the value.
         * @return The value.
         */
        virtual bool getBool(const std::string& key) = 0;

        /**
         * @brief Get value as boolean.
         * @throws ConversionError if type conversion fails.
         * @param Key of the value.
         * @param Default value if key is not found.
         * @return The value.
         */
        virtual bool getBool(const std::string& key, bool devaultValue) = 0;

        /**
         * @brief Get value as float.
         * @throws ConversionError if type conversion fails.
         * @throws MissingValueError if value is not found.
         * @param Key of the value.
         * @return The value.
         */
        virtual float getFloat(const std::string& key) = 0;

        /**
         * @brief Get value as float.
         * @throws ConversionError if type conversion fails.
         * @param Key of the value.
         * @param Default value if key is not found.
         * @return The value.
         */
        virtual float getFloat(const std::string& key, float devaultValue) = 0;

        /**
         * @brief Get value as integer.
         * @throws ConversionError if type conversion fails.
         * @throws MissingValueError if value is not found.
         * @param Key of the value.
         * @return The value.
         */
        virtual int getInt(const std::string& key) = 0;

        /**
         * @brief Get value as integer.
         * @throws ConversionError if type conversion fails.
         * @param Key of the value.
         * @param Default value if key is not found.
         * @return The value.
         */
        virtual int getInt(const std::string& key, int devaultValue) = 0;

        /**
         * @brief Get sub node.
         * @throws MissingValueError if value is not found.
         * @param Key of the value.
         * @return The value.
         */
        virtual ConfigNodePtr getNode(const std::string& key) = 0;

        /**
         * @brief Get value as string.
         * @throws ConversionError if type conversion fails.
         * @throws MissingValueError if value is not found.
         * @param Key of the value.
         * @return The value.
         */
        virtual std::string getString(const std::string& key) = 0;

        /**
         * @brief Get value as string.
         * @throws ConversionError if type conversion fails.
         * @param Key of the value.
         * @param Default value if key is not found.
         * @return The value.
         */
        virtual std::string getString(const std::string& key,
                                      const std::string& devaultValue) = 0;

        /**
         * @brief Check if a value exists.
         * @param Key of the value.
         * @return True if value exists else false.
         */
        virtual bool has(const std::string& key) = 0;
    };
}

#endif // CONFIGNODE_H
