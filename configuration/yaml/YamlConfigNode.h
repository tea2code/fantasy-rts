#ifndef YAMLCONFIGNODE_H
#define YAMLCONFIGNODE_H

#include <configuration/ConfigNode.h>

#include <yaml-cpp/yaml.h>


namespace frts
{
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
        bool getBool(const std::string& key, bool devaultValue);

        float getFloat(const std::string& key);
        float getFloat(const std::string& key, float devaultValue);

        int getInt(const std::string& key);
        int getInt(const std::string& key, int devaultValue);

        ConfigNodePtr getNode(const std::string& key);

        std::string getString(const std::string& key);
        std::string getString(const std::string& key,
                                      const std::string& devaultValue);
        bool has(const std::string& key);
    };
}

#endif // YAMLCONFIGNODE_H
