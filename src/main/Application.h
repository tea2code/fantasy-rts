#ifndef FRTS_APPLICATION_H
#define FRTS_APPLICATION_H

#include "log/Log.h"

#include <string>
#include <vector>


namespace frts
{
    class Application
    {
    public:
        /**
         * @brief Represents the configuration of a load file.
         */
        struct LoadConfiguration
        {
            std::vector<std::string> configurations;
            std::vector<std::string> plugins;
            std::vector<std::string> renderModules;
            std::vector<std::string> updateModules;
            std::vector<std::string> utilities;
        };

    public:
        /**
         * @param log The logger.
         */
        Application(LogPtr log);

        /**
         * @brief Read and parse the file containing the load configuration.
         * @param filePath Path to load file.
         */
        LoadConfiguration readLoadFile(const std::string& filePath) const;

    private:
        LogPtr log;
    };
}

#endif // FRTS_APPLICATION_H
