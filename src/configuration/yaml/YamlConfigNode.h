#ifndef YAMLCONFIGNODE_H
#define YAMLCONFIGNODE_H

#include <configuration/ConfigNode.h>

#include <yaml-cpp/yaml.h>


namespace frts
{
    class ConversionError;
    class MissingValueError;

    /**
     * @brief Implementation of ConfigNode using YAML.
     */
    class YamlConfigNode : public ConfigNode
    {
    public:
        YamlConfigNode(const YAML::Node& node);
        ~YamlConfigNode();

        Iterator begin();
        Iterator end();

        bool getBool(const std::string& key);
        bool getBool(const std::string& key, bool defaultValue);
        std::vector<bool> getBools(const std::string& key);

        double getFloat(const std::string& key);
        double getFloat(const std::string& key, double defaultValue);
        std::vector<double> getFloats(const std::string& key);

        long getInteger(const std::string& key);
        long getInteger(const std::string& key, long defaultValue);
        std::vector<long> getIntegers(const std::string& key);

        ConfigNodePtr getNode(const std::string& key);

        std::string getString(const std::string& key);
        std::string getString(const std::string& key, const std::string& defaultValue);
        std::vector<std::string> getStrings(const std::string& key);

        bool has(const std::string& key);

        bool isBool(const std::string& key);
        bool isFloat(const std::string& key);
        bool isInteger(const std::string& key);
        bool isString(const std::string& key);

    private:
        YAML::Node node;

    private:
        template<typename T>
        T get(const std::string& key, const std::string& type);

        template<typename T>
        T getDefault(const std::string& key, T defaultValue);

        template<typename T>
        bool is(const std::string& key);

        ConversionError makeConversionError(const std::string& key, const std::string& type);
        MissingValueError makeMissingValueError(const std::string& key);
    };
}

#endif // YAMLCONFIGNODE_H
