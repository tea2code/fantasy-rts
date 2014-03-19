#ifndef YAMLCONFIGPARSER_H
#define YAMLCONFIGPARSER_H

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
        ~YamlConfigParser();

        ConfigNodePtr parseFile(const std::string& filePath);
    };
}

#endif // YAMLCONFIGPARSER_H
