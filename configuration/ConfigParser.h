#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include "ConfigNode.h"

#include <string>


namespace frts
{
    /**
     * @brief Interface of configuration parser.
     */
    class ConfigParser
    {
    public:
        virtual ~ConfigParser() {}

        /**
         * @brief Parses the given configuration file.
         * @throws FileNotFoundError if file is not found.
         * @param filePath The path to the configuration file with extension.
         * @return The config node of the root element in the config file.
         */
        virtual ConfigNodePtr parseFile(const std::string& filePath) = 0;
    };
}

#endif // CONFIGPARSER_H
