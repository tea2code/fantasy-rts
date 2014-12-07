#ifndef UNIT_TEST

#include "Application.h"
#include "MainLoop.h"
#include <log/EasyloggingLog.h>
#include <module/Module.h>
#include <module/ModulePtr.h>
#include <module/Tickable.h>
#include <module/Utility.h>
#include <shared/Id.h>
#include <shared/MainIds.h>
#include <shared/impl/FrameImpl.h>
#include <shared/impl/MainDataImpl.h>
#include <shared/impl/SharedManagerImpl.h>

#include <frts/random.h>

#include <boost/format.hpp>

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <memory>
#include <iostream>
#include <string>
#include <vector>


/**
 * @brief Check if command line options exist. See http://stackoverflow.com/a/868894/1931663.
 * @param begin Begin of options.
 * @param end End of options.
 * @param option The option key.
 * @return True if key exists else false.
 */
bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

/**
 * @brief Get command line options. See http://stackoverflow.com/a/868894/1931663.
 * @param begin Begin of options.
 * @param end End of options.
 * @param option The option key.
 * @return The option value.
 */
char* getCmdOption(char** begin, char** end, const std::string& option)
{
    char** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

/**
 * @brief Write load config to log.
 * @param log The log.
 * @param logModule The log module.
 * @param key The key.
 * @param values The values.
 */
void logLoadConfigList(frts::LogPtr log, const std::string& logModule,
                       const std::string& key, const std::vector<std::string>& values)
{
    log->warning(logModule, "\t" + key);
    for(const auto& value : values)
    {
        log->warning(logModule, "\t\t-" + value);
    }
}

int main(int argc, char* argv[])
{
    // Parse arguments.
    if (cmdOptionExists(argv, argv+argc, "help"))
    {
        std::cout << "Command line options:" << std::endl;
        std::cout << "help - Produce this help message." << std::endl;
        std::cout << "deltaTime - Set length of one frame." << std::endl;
        std::cout << "loadFile - File name of load file." << std::endl;
        std::cout << "logConfigFile - Path to log config file." << std::endl;
        std::cout << "maxFrameTime - Maximum length of a frame." << std::endl;
        std::cout << "pluginsRoot - Path to plugins root directory." << std::endl;
        std::cout << "Example: deltaTime 10 loadFile load.yaml" << std::endl;
        return 0;
    }

    // Most basic configuration.
    const frts::Frame::time deltaTime = frts::fromMilliseconds(
                cmdOptionExists(argv, argv+argc, "deltaTime") ?
                std::atoi(getCmdOption(argv, argv+argc, "deltaTime")) : 10
    );
    const std::string loadFile = cmdOptionExists(argv, argv+argc, "loadFile") ?
                getCmdOption(argv, argv+argc, "loadFile") : "load.yaml";
    const std::string logConfigFile = cmdOptionExists(argv, argv+argc, "logConfigFile") ?
                getCmdOption(argv, argv+argc, "logConfigFile") : "log/easylogging.conf";
    const frts::Frame::time maxFrameTime = frts::fromMilliseconds(
                cmdOptionExists(argv, argv+argc, "maxFrameTime") ?
                std::atoi(getCmdOption(argv, argv+argc, "maxFrameTime")) : 100
    );
    const std::string pluginsRoot = cmdOptionExists(argv, argv+argc, "pluginsRoot") ?
                getCmdOption(argv, argv+argc, "pluginsRoot") : "plugins/";

    const std::string logModule = "frts::Kernel";

    // Create logger.
    frts::LogPtr log = frts::makeEasyloggingLog(logConfigFile);

    // Log basic configuration.
    log->warning(logModule, "Basic configuration:");
    log->warning(logModule, "\tdeltaTime = " + std::to_string(deltaTime.count()));
    log->warning(logModule, "\tloadFile = " + loadFile);
    log->warning(logModule, "\tlogConfigFile = " + logConfigFile);
    log->warning(logModule, "\tmaxFrameTime = " + std::to_string(maxFrameTime.count()));
    log->warning(logModule, "\tpluginsRoot = " + pluginsRoot);

    // Start application.
    log->info(logModule, "Start application");
    frts::Application app(log);

    try
    {
        // Phase 1: Read load configuration.
        log->info(logModule, "Phase 1: Read load configuration.");
        auto loadConfig = app.readLoadFile(pluginsRoot + loadFile);
        log->warning(logModule, "Load configuration:");
        logLoadConfigList(log, logModule, "Plugins", loadConfig.plugins);
        logLoadConfigList(log, logModule, "Startup Modules", loadConfig.startupModules);
        logLoadConfigList(log, logModule, "Shutdown Modules", loadConfig.shutdownModules);
        logLoadConfigList(log, logModule, "Render Modules", loadConfig.renderModules);
        logLoadConfigList(log, logModule, "Update Modules", loadConfig.updateModules);
        logLoadConfigList(log, logModule, "Utilities", loadConfig.utilities);
        logLoadConfigList(log, logModule, "Configurations", loadConfig.configurations);

        // Phase 2: Load plugins.
        log->info(logModule, "Phase 2: Load plugins.");
        app.loadPlugins(pluginsRoot, loadConfig.plugins);

        // Create shared manager.
        log->info(logModule, "Create shared manager.");
        frts::SharedManagerImplPtr shared = frts::makeSharedManager(log);

        // Phase 3: Get modules.
        log->info(logModule, "Phase 3: Get modules.");
        // Keep lists of modules for following phases.
        auto startupModules = app.findTickables(loadConfig.startupModules);
        auto shutdownModules = app.findTickables(loadConfig.shutdownModules);
        auto renderModules = app.findTickables(loadConfig.renderModules);
        auto updateModules = app.findTickables(loadConfig.updateModules);
        shared->setRenderModules(renderModules);
        shared->setUpdateModules(updateModules);
        std::vector<frts::UtilityPtr> utilityModules;
        for(const auto& moduleName : loadConfig.utilities)
        {
            auto loadId = shared->makeId(moduleName);
            auto utilityModule = app.findUtility(loadId);
            utilityModules.push_back(utilityModule);
            auto moduleId = shared->makeId(utilityModule->getTypeName());
            shared->setUtility(moduleId, utilityModule);
        }

        // Collect all modules in one list for more convenient use.
        std::vector<frts::ModulePtr> modules;
        std::copy(startupModules.begin(), startupModules.end(),
                  std::back_insert_iterator<decltype(modules)>(modules));
        std::copy(shutdownModules.begin(), shutdownModules.end(),
                  std::back_insert_iterator<decltype(modules)>(modules));
        std::copy(renderModules.begin(), renderModules.end(),
                  std::back_insert_iterator<decltype(modules)>(modules));
        std::copy(updateModules.begin(), updateModules.end(),
                  std::back_insert_iterator<decltype(modules)>(modules));
        std::copy(utilityModules.begin(), utilityModules.end(),
                  std::back_insert_iterator<decltype(modules)>(modules));

        // Log all modules with name, type and version.
        log->warning(logModule, "Following modules were loaded:");
        for (auto module : modules)
        {
            auto msg = boost::format(R"(-Module "%1%" (Version %4%) of type "%2%" (Version %3%).)")
                    % module->getName() % module->getTypeName()
                    % module->getTypeVersion() % module->getVersion();
            log->warning(logModule, "\t" + msg.str());
        }

        // Phase 4: Check required modules.
        log->info(logModule, "Phase 4: Check required modules.");
        app.validateRequiredModules(modules, shared);

        // Phase 5: Preinitialize modules.
        log->info(logModule, "Phase 5: Preinitialize modules.");
        app.preInit(modules, shared);

        // Phase 6: Create data.
        log->info(logModule, "Phase 6: Create data.");
        shared->setDataValue(shared->makeId(frts::MainIds::mainData()), frts::makeMainData(pluginsRoot));
        app.createData(modules, shared);

        // Log all data values with name, type and version.
        log->warning(logModule, "Following data values were loaded:");
        for (auto dataValue : shared->getDataValues())
        {
            auto msg = boost::format(R"(-Data value "%1%" (Version %4%) of type "%2%" (Version %3%).)")
                    % dataValue->getName() % dataValue->getTypeName()
                    % dataValue->getTypeVersion() % dataValue->getVersion();
            log->warning(logModule, "\t" + msg.str());
        }

        // Phase 7: Register main config keys.
        log->info(logModule, "Phase 7: Register main config keys.");
        auto supportedKeys = app.registerConfigKeys(modules);

        // Phase 8: Read config.
        log->info(logModule, "Phase 8: Read config.");
        app.readConfig(supportedKeys, shared, pluginsRoot, loadConfig.configurations);

        // Phase 9: Validate data.
        log->info(logModule, "Phase 9: Validate data.");
        app.validateData(modules, shared);

        // Phase 10: Initialize modules.
        log->info(logModule, "Phase 10: Initialize modules.");
        app.init(modules, shared);

        // Phase 11: Startup.
        log->info(logModule, "Phase 11: Startup");
        app.executeModules(startupModules, shared);

        // Clean up no longer needed lists of modules.
        startupModules.clear();
        renderModules.clear();
        updateModules.clear();
        utilityModules.clear();
        modules.clear();

        // Phase 12: Run game.
        log->info(logModule, "Phase 12: Run game.");
        frts::MainLoop mainLoop(deltaTime, maxFrameTime);
        mainLoop.start(shared);

        // Phase 13: Shutdown.
        log->info(logModule, "Phase 13: Shutdown");
        app.executeModules(shutdownModules, shared);

        // Clean up no longer needed lists of modules.
        shutdownModules.clear();

        // Phase 14: All done. Good night.
        log->info(logModule, "Phase 14: Application finished.");
        return 0;
    }
    catch(const std::exception& ex)
    {
        // Something bad happened.
        log->error(logModule, ex.what());
        return 1;
    }
}

#else

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#endif
