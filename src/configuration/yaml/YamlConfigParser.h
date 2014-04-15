#ifndef FRTS_YAMLCONFIGPARSER_H
#define FRTS_YAMLCONFIGPARSER_H

#include <configuration/ConfigParser.h>


namespace frts
{
    /**
     * @brief Implementation of ConfigParser using YAML.
     */
    class YamlConfigParser : public ConfigParser
    {
    public:
        YamlConfigParser();
        ~YamlConfigParser() override;

        ConfigNodePtr parseFile(const std::string& filePath) override;
    };
}

#endif // FRTS_YAMLCONFIGPARSER_H
