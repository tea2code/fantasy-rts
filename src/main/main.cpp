#ifndef UNIT_TEST

#include "Application.h"
#include "MainLoop.h"
#include <log/EasyloggingLog.h>
#include <module/Module.h>
#include <module/ModulePtr.h>
#include <module/Tickable.h>
#include <module/Utility.h>
#include <shared/impl/FrameImpl.h>
#include <shared/impl/IdImpl.h>
#include <shared/impl/SharedManagerImpl.h>

#include <algorithm>
#include <cstdlib>
#include <memory>
#include <ostream>
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
    frts::LogPtr log = std::make_shared<frts::EasyloggingLog>(logConfigFile);

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
        frts::SharedManagerImplPtr shared = std::make_shared<frts::SharedManagerImpl>(log);

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
            frts::IdPtr id = frts::makeId(moduleName);
            frts::UtilityPtr utilityModule = app.findUtility(id);
            utilityModules.push_back(utilityModule);
            shared->setUtility(id, utilityModule);
        }

        // Phase 4: Check required modules.
        log->info(logModule, "Phase 4: Check required modules.");
        std::vector<frts::ModulePtr> modules;
        for (auto& module : startupModules)
        {
            modules.push_back(module);
        }
        for (auto& module : shutdownModules)
        {
            modules.push_back(module);
        }
        for (auto& module : renderModules)
        {
            modules.push_back(module);
        }
        for (auto& module : updateModules)
        {
            modules.push_back(module);
        }
        for (auto& module : utilityModules)
        {
            modules.push_back(module);
        }
        app.validateRequiredModules(modules, shared);

        // Phase 5: Create data.
        log->info(logModule, "Phase 5: Create data.");
        app.createData(modules, shared);

        // Phase 6: Register main config keys.
        log->info(logModule, "Phase 6: Register main config keys.");
        auto supportedKeys = app.registerConfigKeys(modules);

        // Phase 7: Read config.
        log->info(logModule, "Phase 7: Read config.");
        app.readConfig(supportedKeys, shared, pluginsRoot, loadConfig.configurations);

        // Phase 8: Validate data.
        log->info(logModule, "Phase 8: Validate data.");
        app.validateData(modules, shared);

        // Phase 9: Initialize modules.
        log->info(logModule, "Phase 9: Initialize modules.");
        app.init(modules, shared);

        // Phase 10: Startup.
        log->info(logModule, "Phase 10: Startup");
        app.executeModules(startupModules, shared);

        // Clean up no longer needed lists of modules.
        startupModules.clear();
        renderModules.clear();
        updateModules.clear();
        utilityModules.clear();
        modules.clear();

        // Phase 11: Run game.
        log->info(logModule, "Phase 11: Run game.");
        frts::MainLoop mainLoop(deltaTime, maxFrameTime);
        mainLoop.start(shared);

        // Phase 12: Shutdown.
        log->info(logModule, "Phase 12: Shutdown");
        app.executeModules(shutdownModules, shared);

        // Clean up no longer needed lists of modules.
        shutdownModules.clear();

        // Phase 13: All done. Good night.
        log->info(logModule, "Phase 13: Application finished.");
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
