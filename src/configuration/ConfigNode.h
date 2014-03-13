#ifndef CONFIGNODE_H
#define CONFIGNODE_H

#include "ConfigNodeItr.h"
#include "IteratorWrapper.h"

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
    class ConfigNode;
    using ConfigNodePtr = std::shared_ptr<ConfigNode>;

    /**
     * @brief Interface of configuration nodes.
     */
    class ConfigNode
    {
    public:
        /**
         *
         */
        using Iterator = IteratorWrapper<ConfigNodeItr, ConfigNodePtr, ConfigNodePtr, ConfigNodePtr>;

        virtual ~ConfigNode() {}

        /**
         * @brief begin
         * @return
         */
        virtual Iterator begin() = 0;

        /**
         * @brief end
         * @return
         */
        virtual Iterator end() = 0;

        /**
         * @brief getBool
         * @param key
         * @return
         */
        virtual bool getBool(const std::string& key) = 0;

        /**
         * @brief getBool
         * @param key
         * @param devaultValue
         * @return
         */
        virtual bool getBool(const std::string& key, bool devaultValue) = 0;

        /**
         * @brief getFloat
         * @param key
         * @return
         */
        virtual float getFloat(const std::string& key) = 0;

        /**
         * @brief getFloat
         * @param key
         * @param devaultValue
         * @return
         */
        virtual float getFloat(const std::string& key, float devaultValue) = 0;

        /**
         * @brief getInt
         * @param key
         * @return
         */
        virtual int getInt(const std::string& key) = 0;

        /**
         * @brief getInt
         * @param key
         * @param devaultValue
         * @return
         */
        virtual int getInt(const std::string& key, int devaultValue) = 0;

        /**
         * @brief getMap
         * @param key
         * @return
         */
        template<typename KT, typename VT>
        std::map<KT, VT> getMap(const std::string& key) {}

        /**
         * @brief getMap
         * @param key
         * @param defaultValue
         * @return
         */
        template<typename KT, typename VT>
        std::map<KT, VT> getMap(const std::string& key,
                                const std::map<KT, VT>& defaultValue) {}

        /**
         * @brief getNode
         * @param key
         * @return
         */
        virtual ConfigNodePtr getNode(const std::string& key) = 0;

        /**
         * @brief getString
         * @param key
         * @return
         */
        virtual std::string getString(const std::string& key) = 0;

        /**
         * @brief getString
         * @param key
         * @param devaultValue
         * @return
         */
        virtual std::string getString(const std::string& key,
                                      const std::string& devaultValue) = 0;

        /**
         * @brief getVector
         * @param key
         * @return
         */
        template<typename T>
        std::vector<T> getVector(const std::string& key) {}

        /**
         * @brief getVector
         * @param key
         * @param defaultValue
         * @return
         */
        template<typename T>
        std::vector<T> getVector(const std::string& key,
                                const std::vector<T>& defaultValue) {}

        /**
         * @brief has
         * @param key
         * @return
         */
        virtual bool has(const std::string& key) = 0;

        /**
         * @brief isType
         * @param key
         * @return
         */
        virtual bool isType(const std::string& key) = 0;
    };
}

#endif // CONFIGNODE_H
