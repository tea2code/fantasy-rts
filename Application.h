#ifndef APPLICATION_H
#define APPLICATION_H

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
        Application();

        /**
         * @brief Read and parse the file containing the load configuration.
         * @param filePath Path to load file.
         */
        LoadConfiguration readLoadFile(const std::string& filePath);
    };
}

#endif // APPLICATION_H
