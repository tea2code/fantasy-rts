#ifndef FRTS_APPLICATION_H
#define FRTS_APPLICATION_H

#include <log/Log.h>
#include <module/ModulePtr.h>
#include <plugin/PluginManager.h>
#include <shared/SharedPtr.h>

#include <map>
#include <string>
#include <vector>


namespace frts
{
    /**
     * @brief Thrown if maximum number of extra executions is reached and a
     *        possible dead locking was detected.
     */
    class DeadLockError : public std::runtime_error
    {
    public:
        explicit DeadLockError(const std::string& msg) : std::runtime_error(msg) {}
    };

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
            std::vector<std::string> shutdownModules;
            std::vector<std::string> startupModules;
            std::vector<std::string> updateModules;
            std::vector<std::string> utilities;
        };

    public:
        /**
         * @param log The logger.
         */
        explicit Application(const LogPtr& log);

        /**
         * @brief Validate that all required data values are available.
         * @param modules The modules which should validate.
         * @param shared The shared manager.
         */
        void checkRequiredDataValues(const std::vector<ModulePtr>& modules,
                                     const SharedManagerPtr& shared) const;

        /**
         * @brief Create data objects for modules.
         * @throw DeadLockError if maximum number of extra executions was reached.
         * @param modules The modules.
         * @param shared The shared manager.
         */
        void createData(const std::vector<ModulePtr>& modules, const SharedManagerPtr& shared) const;

        /**
         * @brief Execute given tickable modules.
         * @param modules The modules.
         * @param shared The shared manager.
         */
        void executeModules(const std::vector<TickablePtr>& modules, const SharedManagerPtr& shared) const;

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
        UtilityPtr findUtility(const IdPtr& id);

        /**
         * @brief Initialize given modules with the shared manager.
         * @throw DeadLockError if maximum number of extra executions was reached.
         * @param modules The modules to initialize.
         * @param shared The shared manager.
         */
        void init(const std::vector<ModulePtr>& modules, const SharedManagerPtr& shared) const;

        /**
         * @brief Load libraries and get plugins.
         * @param rootPath The root path of all plugins. Must end with path
         *                 delimiter.
         * @param pluginPaths List of paths to plugins in the root directory.
         */
        void loadPlugins(const std::string& rootPath,
                         const std::vector<std::string>& pluginPaths);

        /**
         * @brief Preinitialize given modules with the shared manager.
         * @throw DeadLockError if maximum number of extra executions was reached.
         * @param modules The modules to initialize.
         * @param shared The shared manager.
         */
        void preInit(const std::vector<ModulePtr>& modules, const SharedManagerPtr& shared) const;

        /**
         * @brief Read configuration.
         * @param supportedKeys List of supported configuration keys and the
         *                      associated modules.
         * @param shared List of shared manager.
         * @param rootPath The root path of all plugins. Must end with path
         *                 delimiter.
         * @param configFiles List of configuration file names.
         */
        void readConfig(const std::map<std::string, std::vector<ModulePtr>>& supportedKeys,
                        const SharedManagerPtr& shared,
                        const std::string& rootPath,
                        const std::vector<std::string>& configFiles) const;

        /**
         * @brief Read and parse the file containing the load configuration.
         * @param filePath Path to load file.
         */
        LoadConfiguration readLoadFile(const std::string& filePath) const;

        /**
         * @brief Let's every module register it's supported configuration keys.
         * @param modules The modules.
         * @return Mapping configuration keys and the modules which support it.
         */
        std::map<std::string, std::vector<ModulePtr>> registerConfigKeys(const std::vector<ModulePtr>& modules) const;

        /**
         * @brief Set maximum number of extra executions (for example in init())
         *        before it is considered a dead lock.
         * @param num Number of executions.
         */
        void setMaxNumberExtraExecutions(unsigned int num = 1000);

        /**
         * @brief Validate that all necessary configuration is loaded (represented
         *        by data values.
         * @param modules The modules which should validate the current config.
         * @param shared The shared manager.
         */
        void validateData(const std::vector<ModulePtr>& modules,
                          const SharedManagerPtr& shared) const;

        /**
         * @brief Validate that all required modules are available aka check
         *        dependencies between modules.
         * @param modules The modules which should validate.
         * @param shared The shared manager.
         */
        void validateRequiredModules(const std::vector<ModulePtr>& modules,
                                     const SharedManagerPtr& shared) const;

    private:
        LogPtr log;
        unsigned int maxNumberExtraExecutions = 0;
        PluginManager pluginManager;
    };
}

#endif // FRTS_APPLICATION_H
