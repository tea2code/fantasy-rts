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

        float getFloat(const std::string& key);
        float getFloat(const std::string& key, float defaultValue);

        int getInt(const std::string& key);
        int getInt(const std::string& key, int defaultValue);

        ConfigNodePtr getNode(const std::string& key);

        std::string getString(const std::string& key);
        std::string getString(const std::string& key,
                                      const std::string& defaultValue);

        bool has(const std::string& key);

        bool isBool(const std::string& key);
        bool isFloat(const std::string& key);
        bool isInt(const std::string& key);
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
