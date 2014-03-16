#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

class frts::ConfigNode;
class std::string;

namespace frts
{
    /**
     * @brief Interface of configuration parser.
     */
    class ConfigParser
    {
    public:
        virtual ~ConfigParser() {}

        ConfigParser(const ConfigParser&) = delete;
        ConfigParser& operator=(const ConfigParser&) = delete;
        ConfigParser(ConfigParser&&) = delete;
        ConfigParser& operator=(ConfigParser&&) = delete;

        /**
         * @brief Parses the given configuration file.
         * @param filePath The path to the configuration file with extension.
         * @return The config node of the root element in the config file.
         */
        virtual frts::ConfigNode parseFile(const std::string& filePath) = 0;
    };
}

#endif // CONFIGPARSER_H
