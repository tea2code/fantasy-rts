#ifndef FRTS_YAMLCONFIGNODE_H
#define FRTS_YAMLCONFIGNODE_H

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
        explicit YamlConfigNode(const YAML::Node& node);
        ~YamlConfigNode() override;

        Iterator begin() override;
        Iterator end() override;

        bool getBool(const std::string& key) override;
        bool getBool(const std::string& key, bool defaultValue) override;
        std::vector<bool> getBools(const std::string& key) override;

        double getFloat(const std::string& key) override;
        double getFloat(const std::string& key, double defaultValue) override;
        std::vector<double> getFloats(const std::string& key) override;

        long getInteger(const std::string& key) override;
        long getInteger(const std::string& key, long defaultValue) override;
        std::vector<long> getIntegers(const std::string& key) override;

        ConfigNodePtr getNode(const std::string& key) override;

        std::string getString(const std::string& key) override;
        std::string getString(const std::string& key, const std::string& defaultValue) override;
        std::vector<std::string> getStrings(const std::string& key) override;

        bool has(const std::string& key) override;

        bool isBool(const std::string& key) override;
        bool isFloat(const std::string& key) override;
        bool isInteger(const std::string& key) override;
        bool isString(const std::string& key) override;

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

#endif // FRTS_YAMLCONFIGNODE_H
