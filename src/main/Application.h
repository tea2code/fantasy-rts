#ifndef FRTS_APPLICATION_H
#define FRTS_APPLICATION_H

#include <log/Log.h>
#include <module/ModulePtr.h>
#include <plugin/PluginManager.h>
#include <shared/SharedPtr.h>

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
         * @brief Create data objects for modules.
         * @param modules The modules.
         * @param shared The shared manager.
         */
        void createData(const std::vector<ModulePtr>& modules, SharedManagerPtr shared) const;

        /**
         * @brief Find tickable modules in loaded plugins.
         * @param moduleNames List of module names.
         * @return List of tickable modules.
         */
        std::vector<TickablePtr> findTickables(const std::vector<std::string>& moduleNames);

        /**
         * @brief Find utility module in loaded plugins.
         * @param id Id of the module.
         * @return List of utility modules.
         */
        UtilityPtr findUtility(IdPtr id);

        /**
         * @brief Load libraries and get plugins.
         * @param rootPath The root path of all plugins. Must end with path
         *                 delimiter.
         * @param pluginPaths List of paths to plugins in the root directory.
         */
        void loadPlugins(const std::string& rootPath,
                         const std::vector<std::string>& pluginPaths);

        /**
         * @brief Read and parse the file containing the load configuration.
         * @param filePath Path to load file.
         */
        LoadConfiguration readLoadFile(const std::string& filePath) const;

        /**
         * @brief Validate that all required modules are available aka check
         *        dependencies between modules.
         * @param modules The modules which should validate.
         * @param shared The shared manager.
         */
        void validateRequiredModules(const std::vector<ModulePtr>& modules,
                                     SharedManagerPtr shared) const;

    private:
        LogPtr log;
        PluginManager pluginManager;
    };
}

#endif // FRTS_APPLICATION_H
