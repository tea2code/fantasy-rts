#ifndef UNIT_TEST

#include "Application.h"
#include <log/EasyloggingLog.h>
#include <module/ModulePtr.h>
#include <shared/impl/IdImpl.h>
#include <shared/impl/SharedManagerImpl.h>

#include <string>
#include <vector>


void logLoadConfigList(frts::LogPtr log, const std::string& logModule,
                       const std::string& key, const std::vector<std::string>& values)
{
    log->warning(logModule, "  " + key);
    for(const auto& value : values)
    {
        log->warning(logModule, "    -" + value);
    }
}

int main()
{
    // Most basic configuration.
    const std::string loadFile = "load.yaml";
    const std::string logConfigFile = "log/easylogging.conf";
    const std::string logModule = "Kernel";
    const std::string pluginsRoot = "plugins/";

    // Create logger.
    frts::LogPtr log = frts::LogPtr(new frts::EasyloggingLog(logConfigFile));

    // Start application.
    log->info(logModule, "Start application");
    frts::Application app(log);

    // Phase 1: Read load configuration.
    log->info(logModule, "Phase 1: Read load configuration.");
    frts::Application::LoadConfiguration loadConfig = app.readLoadFile(pluginsRoot + loadFile);
    log->warning(logModule, "Log configuration:");
    logLoadConfigList(log, logModule, "Plugins", loadConfig.plugins);
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
    // Keep lists of modules for phase 4.
    std::vector<frts::TickablePtr> renderModules = app.findTickables(loadConfig.renderModules);
    std::vector<frts::TickablePtr> updateModules = app.findTickables(loadConfig.updateModules);
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

    // List of modules no longer needed. Clean up.
    renderModules.clear();
    updateModules.clear();
    utilityModules.clear();

    // Phase 5: Create data.
    log->info(logModule, "Phase 5: Create data.");

    // Phase 6: Register main config keys.
    log->info(logModule, "Phase 6: Register main config keys.");

    // Phase 7: Read config.
    log->info(logModule, "Phase 7: Read config.");

    // Phase 8: Validate config.
    log->info(logModule, "Phase 8: Validate config.");

    // Phase 9: Initialize modules.
    log->info(logModule, "Phase 9: Initialize modules.");

    // Run.
    log->info(logModule, "Run game.");
    // ...

    // All done. Good night.
    log->info(logModule, "Application finished.");
    return 0;
}

#else

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#endif
