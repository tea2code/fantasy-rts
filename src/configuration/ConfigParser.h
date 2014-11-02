#ifndef FRTS_CONFIGPARSER_H
#define FRTS_CONFIGPARSER_H

#include "ConfigNodePtr.h"

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
         * @throws FileNotParsableError if file is not parsable aka contains an syntax error.
         * @param filePath The path to the configuration file with extension.
         * @return The config node of the root element in the config file.
         */
        virtual ConfigNodePtr parseFile(const std::string& filePath) = 0;
    };
}

#endif // FRTS_CONFIGPARSER_H
