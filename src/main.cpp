#ifndef UNIT_TEST

#include "Application.h"
#include <log/EasyloggingLog.h>

#include <iostream>
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
    const std::string loadFile = "plugins/load.yaml";
    const std::string logConfigFile = "log/easylogging.conf";
    const std::string logModule = "Kernel";

    // Create logger.
    frts::LogPtr log = frts::LogPtr(new frts::EasyloggingLog(logConfigFile));

    // Start application.
    log->info(logModule, "Start application");
    frts::Application app(log);

    // Read load configuration.
    log->info(logModule, "Read load configuration");
    frts::Application::LoadConfiguration loadConfig = app.readLoadFile(loadFile);
    log->warning(logModule, "Log configuration:");
    logLoadConfigList(log, logModule, "Plugins", loadConfig.plugins);
    logLoadConfigList(log, logModule, "Render Modules", loadConfig.renderModules);
    logLoadConfigList(log, logModule, "Update Modules", loadConfig.updateModules);
    logLoadConfigList(log, logModule, "Utilities", loadConfig.utilities);
    logLoadConfigList(log, logModule, "Configurations", loadConfig.configurations);

    // All done. Good night.
    //std::cin.ignore();
    return 0;
}

#else

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#endif
